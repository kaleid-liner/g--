#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

#include <memory>

using namespace llvm;

Function *genFib(IRBuilder<> &builder, LLVMContext &context, Module *module) {
    auto fib_param_types = std::vector<Type *>{Type::getInt32Ty(context)};

    auto fib_type = FunctionType::get(Type::getInt32Ty(context), fib_param_types, false);
    auto fib = Function::Create(fib_type, GlobalValue::LinkageTypes::ExternalLinkage, "fib", module);
    auto entry = BasicBlock::Create(context, "", fib);

    auto exit = BasicBlock::Create(context, "exit", fib);

    builder.SetInsertPoint(entry);

    auto var_r = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "r"); // %r = alloca i32, align 4
    auto arg0 = fib->args().begin();
    auto zero = builder.getInt32(0);

    auto if0_true = BasicBlock::Create(context, "if0.true", fib, exit);
    auto if0_false = BasicBlock::Create(context, "if0.false", fib, exit);

    auto if0_cond = builder.CreateICmpEQ(arg0, zero, "if0_cond");
    builder.CreateCondBr(if0_cond, if0_true, if0_false);

    // if == 0
    builder.SetInsertPoint(if0_true);
    builder.CreateStore(zero, var_r);
    builder.CreateBr(exit);

    auto if1_true = BasicBlock::Create(context, "if1.true", fib, exit);
    auto if1_false = BasicBlock::Create(context, "if1.false", fib, exit);

    // if != 0
    auto one = builder.getInt32(1);
    builder.SetInsertPoint(if0_false);
    auto if1_cond = builder.CreateICmpEQ(arg0, one, "if1_cond");
    builder.CreateCondBr(if1_cond, if1_true, if1_false);

    // if == 1
    builder.SetInsertPoint(if1_true);
    builder.CreateStore(one, var_r);
    builder.CreateBr(exit);

    // if != 1
    builder.SetInsertPoint(if1_false);
    auto param = builder.CreateSub(arg0, one, "param1", false, true);
    auto fib1 = builder.CreateCall(fib, {param}, "fib1");

    auto two = builder.getInt32(2);
    param = builder.CreateSub(arg0, two, "param2", false, true);
    auto fib2 = builder.CreateCall(fib, {param}, "fib2");

    auto tmp = builder.CreateAdd(fib1, fib2, "tmp", false, true);
    builder.CreateStore(tmp, var_r);
    builder.CreateBr(exit);

    builder.SetInsertPoint(exit);
    tmp = builder.CreateLoad(var_r, "retval");
    builder.CreateRet(tmp);

    builder.ClearInsertionPoint();
    return fib;
}


Function *genMain(IRBuilder<> &builder, LLVMContext &context, Module *module, Function *fib) {
    auto main_type = FunctionType::get(Type::getInt32Ty(context), {}, false);
    auto main = Function::Create(main_type, GlobalValue::LinkageTypes::ExternalLinkage, "main", module);
    auto entry = BasicBlock::Create(context, "", main);

    auto exit = BasicBlock::Create(context, "exit", main);

    builder.SetInsertPoint(entry);
    auto var_x = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "x");

    auto zero = builder.getInt32(0);
    builder.CreateStore(zero, var_x);
    
    auto var_n = builder.CreateAlloca(Type::getFloatTy(context), nullptr, "n");
    auto eightf = ConstantFP::get(Type::getFloatTy(context), 8.0);
    builder.CreateStore(eightf, var_n);

    auto var_i = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "i");
    auto one = builder.getInt32(1);
    builder.CreateStore(one, var_i);

    auto loop_start = BasicBlock::Create(context, "loop.start", main, exit);
    builder.CreateBr(loop_start);

    builder.SetInsertPoint(loop_start);
    auto loop_true = BasicBlock::Create(context, "loop.true", main, exit);

    auto loaded_i = builder.CreateLoad(var_i);
    auto tmp = builder.CreateSIToFP(loaded_i, Type::getFloatTy(context));
    auto loaded_n = builder.CreateLoad(var_n);
    auto loop_cond = builder.CreateFCmpOLT(tmp, loaded_n);
    builder.CreateCondBr(loop_cond, loop_true, exit);

    builder.SetInsertPoint(loop_true);
    tmp = builder.CreateCall(fib, {loaded_i}, "");
    auto loaded_x = builder.CreateLoad(var_x);
    tmp = builder.CreateAdd(tmp, loaded_x, "", false, true);
    builder.CreateStore(tmp, var_x);
    tmp = builder.CreateAdd(one, loaded_i, "", false, true);
    builder.CreateStore(tmp, var_i);
    builder.CreateBr(loop_start);

    builder.SetInsertPoint(exit);
    loaded_x = builder.CreateLoad(var_x);
    builder.CreateRet(loaded_x);

    builder.ClearInsertionPoint();
    return main;
}


int main()
{
    LLVMContext context;
    IRBuilder<> builder(context);

    // Just an example
    auto module = new Module("GenFib", context);

    // gen fib
    auto fib = genFib(builder, context, module);
    genMain(builder, context, module, fib);

    module->print(outs(), nullptr);
    delete module;
    return 0;
}
