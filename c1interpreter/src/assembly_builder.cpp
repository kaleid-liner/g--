
#include "assembly_builder.h"

#include <vector>

using namespace llvm;
using namespace c1_recognizer::syntax_tree;

namespace {
    // a helper function to deal with constant and constexpr conversion
    Constant *get_const(LLVMContext &context, bool is_result_int, bool is_node_int, 
                        int int_const_result = 0, double float_const_result = .0) {
        Constant *constant;
        if (is_result_int) {
            constant = is_node_int ? ConstantInt::get(Type::getInt32Ty(context), int_const_result)
                                   : ConstantFP::get(Type::getDoubleTy(context), int_const_result);
        } else {
            constant = is_node_int ? ConstantInt::get(Type::getInt32Ty(context), float_const_result)
                                   : ConstantFP::get(Type::getDoubleTy(context), float_const_result);
        }
        return constant;
    }

    // convert type from -> to. From_type is int if `from` == true, same applied to `to`
    Value *auto_conversion(IRBuilder<> &builder, LLVMContext &context, Value *v, bool from, bool to) {
        if (from == to) {
            return v;
        }
        if (from) { // int -> float
            return builder.CreateSIToFP(v, Type::getDoubleTy(context));
        } else { // float -> int
            return builder.CreateFPToSI(v, Type::getInt32Ty(context));
        }
    }

    int calc_expr(binop op, int lhs, int rhs) {
        switch (op) {
            case binop::plus:
                return lhs + rhs;
            case binop::minus:  
                return lhs - rhs;
            case binop::multiply:
                return lhs * rhs;
            case binop::divide:
                return lhs / rhs;
            case binop::modulo:
                return lhs % rhs;
            default:
                return 0;
        }
    }

    double calc_expr(binop op, double lhs, double rhs) {
        switch (op) {
            case binop::plus:
                return lhs + rhs;
            case binop::minus:  
                return lhs - rhs;
            case binop::multiply:
                return lhs * rhs;
            case binop::divide:
                return lhs / rhs;
            default:
                return .0;
        }
    }

    Value *calc_expr(IRBuilder<> &builder, binop op, Value *lhs, Value *rhs, bool is_int) {
        if (is_int) {
            switch (op) {
                case binop::plus:
                    return builder.CreateAdd(lhs, rhs, "", false, true);
                case binop::minus:
                    return builder.CreateSub(lhs, rhs, "", false, true);
                case binop::multiply:
                    return builder.CreateMul(lhs, rhs, "", false, true);
                case binop::divide:
                    return builder.CreateSDiv(lhs, rhs);
                case binop::modulo:
                    return builder.CreateSRem(lhs, rhs);
                default:
                    return nullptr;
            }
        } else {
            switch (op) {
                case binop::plus:
                    return builder.CreateFAdd(lhs, rhs);
                case binop::minus:
                    return builder.CreateFSub(lhs, rhs);
                case binop::multiply:
                    return builder.CreateFMul(lhs, rhs);
                case binop::divide:
                    return builder.CreateFDiv(lhs, rhs);
                default:
                    return nullptr;
            }
        }
    }

    int calc_expr(unaryop op, int rhs) {
        switch (op) {
            case unaryop::plus:
                return rhs;
            case unaryop::minus:
                return -rhs;
        }
    }

    double calc_expr(unaryop op ,double rhs) {
        switch (op) {
            case unaryop::plus:
                return rhs;
            case unaryop::minus:
                return -rhs;
        }
    }

    Value *calc_expr(IRBuilder<> &builder, unaryop op, Value *rhs, bool is_int) {
        if (is_int) {
            switch (op) {
                case unaryop::plus:
                    return rhs;
                case unaryop::minus:
                    return builder.CreateNeg(rhs, "", false, true);
                default:
                    return nullptr;
            }
        } else {
            switch (op) {
                case unaryop::plus:
                    return rhs;
                case unaryop::minus:
                    return builder.CreateFNeg(rhs);
                default:
                    return nullptr;
            }
        }
    }

    Value *calc_expr(IRBuilder<> &builder, relop op, Value *lhs, Value *rhs, bool is_int) {
        if (is_int) {
            switch (op) {
                case relop::equal:
                    return builder.CreateICmpEQ(lhs, rhs);
                case relop::non_equal:
                    return builder.CreateICmpNE(lhs, rhs);
                case relop::greater:
                    return builder.CreateICmpSGT(lhs, rhs);
                case relop::greater_equal:
                    return builder.CreateICmpSGE(lhs, rhs);
                case relop::less:
                    return builder.CreateICmpSLT(lhs, rhs);
                case relop::less_equal:
                    return builder.CreateICmpSLE(lhs, rhs);
            }
        } else {
            switch (op) {
                case relop::equal:
                    return builder.CreateFCmpOEQ(lhs, rhs);
                case relop::non_equal:
                    return builder.CreateFCmpONE(lhs, rhs);
                case relop::greater:
                    return builder.CreateFCmpOGT(lhs, rhs);
                case relop::greater_equal:
                    return builder.CreateFCmpOGE(lhs, rhs);
                case relop::less:
                    return builder.CreateFCmpOLT(lhs, rhs);
                case relop::less_equal:
                    return builder.CreateFCmpOLE(lhs, rhs);
            }
        }
    }
}

void assembly_builder::visit(assembly &node)
{
    in_global = true;
    for (auto &def : node.global_defs) {
        def->accept(*this);
    }
}

void assembly_builder::visit(func_def_syntax &node)
{
    if (functions.count(node.name)) {
        error_flag = true;
        err.error(node.line, node.pos, "Function named '" + node.name + "' already exists");
        return;
    }

    current_function = Function::Create(FunctionType::get(Type::getVoidTy(context), {}, false), 
                                        GlobalValue::LinkageTypes::ExternalLinkage, 
                                        node.name, 
                                        module.get());
    functions[node.name] = current_function; // declare function

    bb_count = 0;

    auto entry = BasicBlock::Create(context, "BB" + std::to_string(bb_count++), current_function);
    builder.SetInsertPoint(entry);

    // deal with scope after entering the block
    node.body->accept(*this); // definition body

    builder.CreateRetVoid();
    builder.ClearInsertionPoint(); // To ensure that nothing more is appended to this function
}

void assembly_builder::visit(cond_syntax &node)
{
    constexpr_expected = false;
    lval_as_rval = true;

    node.lhs->accept(*this);
    auto lhs_result = value_result;
    bool is_lhs_int = is_result_int;

    node.rhs->accept(*this);
    auto rhs_result = value_result;
    bool is_rhs_int = is_result_int;

    is_result_int = is_lhs_int && is_rhs_int; // if one of the operands is float, the result is float
    // lhs, rhs : int/float -> int/float
    lhs_result = auto_conversion(builder, context, lhs_result, is_lhs_int, is_result_int);
    rhs_result = auto_conversion(builder, context, rhs_result, is_rhs_int, is_result_int);
    value_result = calc_expr(builder, node.op, lhs_result, rhs_result, is_result_int);
}

void assembly_builder::visit(binop_expr_syntax &node)
{
    if (constexpr_expected) {
        node.lhs->accept(*this);
        if (is_result_int) {
            int lhs_result = int_const_result;
            node.rhs->accept(*this);
            
            if (is_result_int) {
                is_result_int = true;  // redundant assignment
                int_const_result = calc_expr(node.op, lhs_result, int_const_result);
            } else {
                if (node.op == binop::modulo) {
                    error_flag = true;
                    err.error(node.line, node.pos, "Modulo operator not supported on float");
                    return;
                }
                is_result_int = false;
                int_const_result = calc_expr(node.op, (double)lhs_result, float_const_result);
            }
        } else {
            double lhs_result = float_const_result;
            node.rhs->accept(*this);

            if (node.op == binop::modulo) {
                error_flag = true;
                err.error(node.line, node.pos, "Modulo operator not supported on float");
                return;
            }

            if (is_result_int) {
                is_result_int = false;
                float_const_result = calc_expr(node.op, lhs_result, (double)int_const_result);
            } else {
                is_result_int = false;
                float_const_result = calc_expr(node.op, lhs_result, float_const_result);
            }
        }
    } else {
        // lval_as_rval has been set by parents
        node.lhs->accept(*this);
        auto lhs_result = value_result;
        bool is_lhs_int = is_result_int;

        node.rhs->accept(*this);
        auto rhs_result = value_result;
        bool is_rhs_int = is_result_int;

        is_result_int = (!is_lhs_int) || (!is_rhs_int); // if one of the operands is float, the result is float
        // lhs, rhs : int/float -> int/float
        lhs_result = auto_conversion(builder, context, lhs_result, is_lhs_int, is_result_int);
        rhs_result = auto_conversion(builder, context, rhs_result, is_rhs_int, is_result_int);
        value_result = calc_expr(builder, node.op, lhs_result, rhs_result, is_result_int);
    }
}

void assembly_builder::visit(unaryop_expr_syntax &node)
{
    if (constexpr_expected) {
        node.rhs->accept(*this);

        // is_result_int has been set
        if (is_result_int) {
            int_const_result = calc_expr(node.op, int_const_result);
        } else {
            float_const_result = calc_expr(node.op, float_const_result);
        }
    } else {
        node.rhs->accept(*this);

        // is_result_int has been set
        value_result = calc_expr(builder, node.op, value_result, is_result_int);
    }
}

void assembly_builder::visit(lval_syntax &node)
{
    if (constexpr_expected) {
        error_flag = true;
        err.error(node.line, node.pos, "Expected a constexpr but found a left value");
        return;
    }

    auto [var_ptr, is_const, is_array, is_int] = lookup_variable(node.name);

    if (is_const && !lval_as_rval) {
        error_flag = true;
        err.error(node.line, node.pos, "const value can't be assigned");
        return;
    }
    
    if (is_array) {
        if (node.array_index == nullptr) {
            error_flag = true;
            err.error(node.line, node.pos, "Expected index but not found");
            return;
        } else {
            lval_as_rval = true; // lval should be evaluated
            constexpr_expected = false;
            node.array_index->accept(*this);
            if (!is_result_int) {
                error_flag = true;
                err.error(node.line, node.pos, "Array index must be an integer");
                return;
            }

            var_ptr = builder.CreateGEP(var_ptr, value_result);
        }
    }

    if (lval_as_rval) {
        value_result = builder.CreateLoad(var_ptr);
    } else {
        value_result = var_ptr;
    }

    is_result_int = is_int;
}

void assembly_builder::visit(literal_syntax &node)
{
    if (node.is_int) {
        is_result_int = true;
        if (constexpr_expected) {
            int_const_result = node.intConst;
        } else {
            value_result = builder.getInt32(node.intConst);
        }
    } else {
        is_result_int = false;
        if (constexpr_expected) {
            float_const_result = node.floatConst;
        } else {
            value_result = ConstantFP::get(Type::getDoubleTy(context), node.floatConst);
        }
    }
}

void assembly_builder::visit(var_def_stmt_syntax &node)
{
    auto ty = node.is_int ? Type::getInt32Ty(context) : Type::getDoubleTy(context);
    if (node.array_length == nullptr) { // not an array
        if (in_global) { // x array, global
            constexpr_expected = true;
            
            Constant *constant = nullptr;
            if (!node.initializers.empty()) { // initialize
                node.initializers[0]->accept(*this);
                constant = get_const(context, is_result_int, node.is_int, int_const_result, float_const_result);
            }

            auto var = new GlobalVariable(ty, node.is_constant, GlobalValue::ExternalLinkage, constant, node.name);

            // variables with same name
            if (!declare_variable(node.name, var, node.is_constant, false, node.is_int)) {
                err.error(node.line, node.pos, "Symbol '" + node.name + "' already defined");
            }
        } else { // x array, x global
            auto var = builder.CreateAlloca(ty, nullptr);
            if (!declare_variable(node.name, var, node.is_constant, false, node.is_int)) {
                error_flag = true;
                err.error(node.line, node.pos, "Variable named '" + node.name + "' already exists");
                return;
            }

            if (!node.initializers.empty()) {
                constexpr_expected = false;
                lval_as_rval = true; // evaluate lval
                node.initializers[0]->accept(*this);

                // do implicit conversion if needed
                auto value_conv = auto_conversion(builder, context, value_result, is_result_int, node.is_int);
                builder.CreateStore(value_conv, var);
            }
        }
    } else {
        constexpr_expected = true;  // array length need to be constexpr
        node.array_length->accept(*this);

        if (!is_result_int) {
            error_flag = true;
            err.error(node.line, node.pos, "Array length must be an integer");
            return;
        }

        int length = int_const_result;
        if (length < node.initializers.size()) {
            error_flag = true;
            err.error(node.line, node.pos, "Array length shortest than the initializer list");
            return;
        }
        auto array_type = ArrayType::get(ty, length);

        if (in_global) { // array, global
            std::vector<Constant *> elements;

            constexpr_expected = true;
            for (auto &initializer : node.initializers) { // it's ok when initializers is empty
                initializer->accept(*this);
                elements.push_back(get_const(context, is_result_int, node.is_int, int_const_result, float_const_result));
            }

            for (size_t i = node.initializers.size(); i < length; i++) {
                elements.push_back(get_const(context, node.is_int, node.is_int, 0, 0)); // fill the rest with 0
            }

            Constant *constant = ConstantArray::get(array_type, elements);
            auto var = new GlobalVariable(array_type, node.is_constant, GlobalValue::ExternalLinkage, constant, node.name);
            if (!declare_variable(node.name, var, node.is_constant, true, node.is_int)) {
                error_flag = true;
                err.error(node.line, node.pos, "Symbol '" + node.name + "' already defined");
                return;
            }
        } else {
            auto var = builder.CreateAlloca(ty, builder.getInt32(int_const_result));

            constexpr_expected = false;
            lval_as_rval = true;
            for (size_t i = 0; i < node.initializers.size(); i++) {
                node.initializers[i]->accept(*this);

                auto elementptr = builder.CreateGEP(var, builder.getInt32(i));
                auto value_conv = auto_conversion(builder, context, value_result, is_result_int, node.is_int);
                builder.CreateStore(value_conv, elementptr);
            }

            if (!node.initializers.empty()) { // if initializer list is empty, no need to fill the array with zero
                for (size_t i = node.initializers.size(); i < length; i++) {
                    auto elementptr = builder.CreateGEP(var, builder.getInt32(i));
                    builder.CreateStore(get_const(context, node.is_int, node.is_int, 0, 0), elementptr);
                }
            }
        }
    }
}

void assembly_builder::visit(assign_stmt_syntax &node)
{
    constexpr_expected = false;

    // evaluate value first
    lval_as_rval = true;
    node.value->accept(*this);
    auto value = value_result;
    bool value_is_int = is_result_int;

    lval_as_rval = false;
    node.target->accept(*this);
    value = auto_conversion(builder, context, value, value_is_int, is_result_int); // value int/float -> int/float
    builder.CreateStore(value, value_result);
}

void assembly_builder::visit(func_call_stmt_syntax &node)
{
    auto iter = functions.find(node.name); // use find to avoid searching twice
    if (iter != functions.end()) { // not found
        builder.CreateCall(iter->second);
    } else {
        error_flag = true;
        err.error(node.line, node.pos, "No function named '" + node.name + "'");
    }
}

void assembly_builder::visit(block_syntax &node)
{
    // block syntax is a scope, not a basic block
    enter_scope();

    for (auto &stmt : node.body) {
        stmt->accept(*this);
    }

    exit_scope();
}

void assembly_builder::visit(if_stmt_syntax &node)
{
    auto then_body = BasicBlock::Create(context, "BB" + std::to_string(bb_count++), current_function);
    auto else_body = node.else_body ? BasicBlock::Create(context, "BB" + std::to_string(bb_count++), current_function)
                                    : nullptr;
    auto next = BasicBlock::Create(context, "BB" + std::to_string(bb_count++), current_function);

    node.pred->accept(*this);
    builder.CreateCondBr(value_result, then_body, else_body ? else_body : next);

    builder.SetInsertPoint(then_body);
    node.then_body->accept(*this);
    builder.CreateBr(next);

    if (node.else_body) {
        builder.SetInsertPoint(else_body);
        node.else_body->accept(*this);
        builder.CreateBr(next);
    }

    builder.SetInsertPoint(next);
}

void assembly_builder::visit(while_stmt_syntax &node)
{
    auto pred = BasicBlock::Create(context, "BB" + std::to_string(bb_count++), current_function);
    auto loop_body = BasicBlock::Create(context, "BB" + std::to_string(bb_count++), current_function);
    auto next = BasicBlock::Create(context, "BB" + std::to_string(bb_count++), current_function);

    builder.SetInsertPoint(pred);
    node.pred->accept(*this);
    builder.CreateCondBr(value_result, loop_body, next);

    builder.SetInsertPoint(loop_body);
    node.body->accept(*this);
    builder.CreateBr(pred);

    builder.SetInsertPoint(next);
}

void assembly_builder::visit(empty_stmt_syntax &node)
{
    // do nothing
}
