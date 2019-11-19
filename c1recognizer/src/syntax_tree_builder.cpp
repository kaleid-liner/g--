
#include <c1recognizer/syntax_tree_builder.h>
#include <memory>

using namespace c1_recognizer;
using namespace c1_recognizer::syntax_tree;

syntax_tree_builder::syntax_tree_builder(error_reporter &_err) : err(_err) {}

antlrcpp::Any syntax_tree_builder::visitCompilationUnit(C1Parser::CompilationUnitContext *ctx)
{
    auto result = new assembly;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    for (auto def : ctx->children)
    {
        if (auto decl = dynamic_cast<C1Parser::DeclContext *>(def))
        {
            auto defs = visit(decl).as<ptr_list<var_def_stmt_syntax>>();
            for (auto def : defs)
                result->global_defs.push_back(std::dynamic_pointer_cast<global_def_syntax>(def));
        }
        else if (auto funcdef = dynamic_cast<C1Parser::FuncdefContext *>(def))
            result->global_defs.push_back(ptr<global_def_syntax>(visit(funcdef).as<func_def_syntax *>()));
    }
    return result;
}

antlrcpp::Any syntax_tree_builder::visitDecl(C1Parser::DeclContext *ctx)
{
    auto constdecl = ctx->constdecl();
    auto vardecl = ctx->vardecl();
    if (constdecl)
        return visit(constdecl);
    else if (vardecl)
        return visit(vardecl);
    err.error(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), "Unrecognized declaration.");
    return ptr_list<var_def_stmt_syntax>();
}

antlrcpp::Any syntax_tree_builder::visitConstdecl(C1Parser::ConstdeclContext *ctx)
{
    bool is_int;
    // if (!ctx->Int() && !ctx->Float())
    // {
    //     auto curr = ctx->constdef(0)->Identifier()->getSymbol();
    //     err.warn(curr->getLine(), curr->getCharPositionInLine(), "Concrete type missing for const declaration; integer assumed.");
    // }
    // else
    // {
    if (ctx->Int())
        is_int = true;
    else 
        is_int = false;
    // }
    ptr_list<var_def_stmt_syntax> result;
    int i = 0;
    for (auto constdef : ctx->constdef()){
        result.push_back(ptr<var_def_stmt_syntax>(visit(constdef).as<var_def_stmt_syntax *>()));
        result[i++]->is_int = is_int;
    }
    return result;
}

antlrcpp::Any syntax_tree_builder::visitConstdef(C1Parser::ConstdefContext *ctx)
{
    auto result = new var_def_stmt_syntax;
    result->is_constant = true;
    result->name = ctx->Identifier()->getSymbol()->getText();
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    if (ctx->LeftBracket())
    {
        int init_length = ctx->Comma().size() + 1;
        auto exps = ctx->exp();
        int init_start = 0;
        if (exps.size() == init_length)
        {
            auto len = new literal_syntax;
            len->is_int = true;
            len->intConst = init_length;
            len->line = ctx->RightBracket()->getSymbol()->getLine();
            len->pos = ctx->RightBracket()->getSymbol()->getCharPositionInLine();
            result->array_length.reset(len);
        }
        else if (exps.size() == init_length + 1)
        {
            result->array_length.reset(visit(exps[0]).as<expr_syntax *>());
            init_start = 1;
        }
        /*else*/ // Should never happen.
        for (int i = init_start; i < init_start + init_length; ++i)
            result->initializers.push_back(ptr<expr_syntax>(visit(exps[i]).as<expr_syntax *>()));
    }
    else
        result->initializers.push_back(ptr<expr_syntax>(visit(ctx->exp(0)).as<expr_syntax *>()));
    return result;
}

antlrcpp::Any syntax_tree_builder::visitVardecl(C1Parser::VardeclContext *ctx)
{
    bool is_int;
    if (ctx->Int())
        is_int = true;
    else 
        is_int = false;

    ptr_list<var_def_stmt_syntax> result;
    int i = 0;
    for (auto vardef : ctx->vardef()){
        result.push_back(ptr<var_def_stmt_syntax>(visit(vardef).as<var_def_stmt_syntax *>()));
        result[i++]->is_int = is_int;
    }
    return result;
}

antlrcpp::Any syntax_tree_builder::visitVardef(C1Parser::VardefContext *ctx)
{
    auto result = new var_def_stmt_syntax;
    result->is_constant = false;
    result->name = ctx->Identifier()->getSymbol()->getText();
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    if (ctx->LeftBracket())
    {
        if (ctx->Assign())
        {
            int init_length = ctx->Comma().size() + 1;
            auto exps = ctx->exp();
            int init_start = 0;
            if (exps.size() == init_length)
            {
                auto len = new literal_syntax;
                len->is_int = true;
                len->intConst = init_length;
                len->line = ctx->RightBracket()->getSymbol()->getLine();
                len->pos = ctx->RightBracket()->getSymbol()->getCharPositionInLine();
                result->array_length.reset(len);
            }
            else if (exps.size() == init_length + 1)
            {
                result->array_length.reset(visit(exps[0]).as<expr_syntax *>());
                init_start = 1;
            }
            /*else*/ // Should never happen.
            for (int i = init_start; i < init_start + init_length; ++i)
                result->initializers.push_back(ptr<expr_syntax>(visit(exps[i]).as<expr_syntax *>()));
        }
        else
            result->array_length.reset(visit(ctx->exp(0)).as<expr_syntax *>());
    }
    else if (ctx->Assign())
        result->initializers.push_back(ptr<expr_syntax>(visit(ctx->exp(0)).as<expr_syntax *>()));
    return result;
}

antlrcpp::Any syntax_tree_builder::visitFuncdef(C1Parser::FuncdefContext *ctx)
{
    auto result = new func_def_syntax;
    result->name = ctx->Identifier()->getSymbol()->getText();
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->body.reset(visit(ctx->block()).as<block_syntax *>());
    return result;
}

antlrcpp::Any syntax_tree_builder::visitBlock(C1Parser::BlockContext *ctx)
{
    auto result = new block_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    for (auto subtree : ctx->children)
        if (auto stmt = dynamic_cast<C1Parser::StmtContext *>(subtree))
            result->body.push_back(ptr<stmt_syntax>(visit(stmt).as<stmt_syntax *>()));
        else if (auto decl = dynamic_cast<C1Parser::DeclContext *>(subtree))
        {
            auto defs = visit(decl).as<ptr_list<var_def_stmt_syntax>>();
            for (auto def : defs)
                result->body.push_back(std::dynamic_pointer_cast<stmt_syntax>(def));
        }
    return result;
}

antlrcpp::Any syntax_tree_builder::visitStmt(C1Parser::StmtContext *ctx)
{
    if (auto lval = ctx->lval())
    {
        auto result = new assign_stmt_syntax;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        result->target.reset(visit(lval).as<lval_syntax *>());
        result->value.reset(visit(ctx->exp()).as<expr_syntax *>());
        return static_cast<stmt_syntax *>(result);
    }
    else if (auto id = ctx->Identifier())
    {
        auto result = new func_call_stmt_syntax;
        result->name = id->getSymbol()->getText();
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        return static_cast<stmt_syntax *>(result);
    }
    else if (auto block = ctx->block())
        return static_cast<stmt_syntax *>(visit(block).as<block_syntax *>());
    else if (ctx->If())
    {
        auto result = new if_stmt_syntax;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        result->pred.reset(visit(ctx->cond()).as<cond_syntax *>());
        auto stmts = ctx->stmt();
        result->then_body.reset(visit(stmts[0]).as<stmt_syntax *>());
        if (stmts.size() > 1)
            result->else_body.reset(visit(stmts[1]).as<stmt_syntax *>());
        return static_cast<stmt_syntax *>(result);
    }
    else if (ctx->While())
    {
        auto result = new while_stmt_syntax;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        result->pred.reset(visit(ctx->cond()).as<cond_syntax *>());
        result->body.reset(visit(ctx->stmt(0)).as<stmt_syntax *>());
        return static_cast<stmt_syntax *>(result);
    }
    else
    {
        auto result = new empty_stmt_syntax;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        return static_cast<stmt_syntax *>(result);
    }
}

antlrcpp::Any syntax_tree_builder::visitLval(C1Parser::LvalContext *ctx)
{
    auto result = new lval_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->name = ctx->Identifier()->getSymbol()->getText();
    if (auto e = ctx->exp())
        result->array_index.reset(visit(e).as<expr_syntax *>());
    return result;
}

antlrcpp::Any syntax_tree_builder::visitCond(C1Parser::CondContext *ctx)
{
    auto result = new cond_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->lhs.reset(visit(ctx->exp(0)).as<expr_syntax *>());
    if (ctx->Equal())
        result->op = relop::equal;
    if (ctx->NonEqual())
        result->op = relop::non_equal;
    if (ctx->Less())
        result->op = relop::less;
    if (ctx->LessEqual())
        result->op = relop::less_equal;
    if (ctx->Greater())
        result->op = relop::greater;
    if (ctx->GreaterEqual())
        result->op = relop::greater_equal;
    result->rhs.reset(visit(ctx->exp(1)).as<expr_syntax *>());
    return result;
}

// Returns antlrcpp::Any, which is constructable from any type.
// However, you should be sure you use the same type for packing and depacking the `Any` object.
// Or a std::bad_cast exception will rise.
// This function always returns an `Any` object containing a `expr_syntax *`.
antlrcpp::Any syntax_tree_builder::visitExp(C1Parser::ExpContext *ctx)
{
    // Get all sub-contexts of type `exp`.
    auto expressions = ctx->exp();
    // Two sub-expressions presented: this indicates it's a expression of binary operator, aka `binop`.
    if (expressions.size() == 2)
    {
        auto result = new binop_expr_syntax;
        // Set line and pos.
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        // visit(some context) is equivalent to calling corresponding visit method; dispatching is done automatically
        // by ANTLR4 runtime. For this case, it's equivalent to visitExp(expressions[0]).
        // Use reset to set a new pointer to a std::shared_ptr object. DO NOT use assignment; it won't work.
        // Use `.as<Type>()' to get value from antlrcpp::Any object; notice that this Type must match the type used in
        // constructing the Any object, which is constructed from (usually pointer to some derived class of
        // syntax_node, in this case) returning value of the visit call.
        result->lhs.reset(visit(expressions[0]).as<expr_syntax *>());
        // Check if each token exists.
        // Returnd value of the calling will be nullptr (aka NULL in C) if it isn't there; otherwise non-null pointer.
        if (ctx->Plus())
            result->op = binop::plus;
        if (ctx->Minus())
            result->op = binop::minus;
        if (ctx->Multiply())
            result->op = binop::multiply;
        if (ctx->Divide())
            result->op = binop::divide;
        if (ctx->Modulo())
            result->op = binop::modulo;
        result->rhs.reset(visit(expressions[1]).as<expr_syntax *>());
        return static_cast<expr_syntax *>(result);
    }
    // Otherwise, if `+` or `-` presented, it'll be a `unaryop_expr_syntax`.
    if (ctx->Plus() || ctx->Minus())
    {
        auto result = new unaryop_expr_syntax;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        if (ctx->Plus())
            result->op = unaryop::plus;
        if (ctx->Minus())
            result->op = unaryop::minus;
        result->rhs.reset(visit(expressions[0]).as<expr_syntax *>());
        return static_cast<expr_syntax *>(result);
    }
    // In the case that `(` exists as a child, this is an expression like `'(' expressions[0] ')'`.
    if (ctx->LeftParen())
        return visit(expressions[0]); // Any already holds expr_syntax* here, no need for dispatch and re-patch with casting.
    if (auto lval = ctx->lval())
        return static_cast<expr_syntax *>(visit(lval).as<lval_syntax *>());
    // If `number` exists as a child, we can say it's a literal integer expression.
    if (auto number = ctx->number())
    {
        return visit(number);
    }
}

antlrcpp::Any syntax_tree_builder::visitNumber(C1Parser::NumberContext *ctx)
{
    if (auto intConst = ctx->IntConst())
    {
        auto result = new literal_syntax;
        result->is_int = true;
        result->line = intConst->getSymbol()->getLine();
        result->pos = intConst->getSymbol()->getCharPositionInLine();
        auto text = intConst->getSymbol()->getText();
        if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) // Hexadecimal
            result->intConst = std::stoi(text, nullptr, 16); // std::stoi will eat '0x'
        else if (text[0] == '0')                             // Octal
            result->intConst = std::stoi(text, nullptr, 8);  // std::stoi will eat '0'
        else                                                 // Decimal
            result->intConst = std::stoi(text, nullptr, 10);

        return static_cast<expr_syntax *>(result);
    }
    // else FloatConst
    else
    {
        auto floatConst = ctx->FloatConst(); 
        auto result = new literal_syntax;
        result->is_int = false;
        result->line = floatConst->getSymbol()->getLine();
        result->pos = floatConst->getSymbol()->getCharPositionInLine();
        auto text = floatConst->getSymbol()->getText();
        result->floatConst = std::stod(text); // just call stod
        return static_cast<expr_syntax *>(result);
    }
}

ptr<syntax_tree_node> syntax_tree_builder::operator()(antlr4::tree::ParseTree *ctx)
{
    auto result = visit(ctx);
    if (result.is<syntax_tree_node *>())
        return ptr<syntax_tree_node>(result.as<syntax_tree_node *>());
    if (result.is<assembly *>())
        return ptr<syntax_tree_node>(result.as<assembly *>());
    if (result.is<global_def_syntax *>())
        return ptr<syntax_tree_node>(result.as<global_def_syntax *>());
    if (result.is<func_def_syntax *>())
        return ptr<syntax_tree_node>(result.as<func_def_syntax *>());
    if (result.is<cond_syntax *>())
        return ptr<syntax_tree_node>(result.as<cond_syntax *>());
    if (result.is<expr_syntax *>())
        return ptr<syntax_tree_node>(result.as<expr_syntax *>());
    if (result.is<binop_expr_syntax *>())
        return ptr<syntax_tree_node>(result.as<binop_expr_syntax *>());
    if (result.is<unaryop_expr_syntax *>())
        return ptr<syntax_tree_node>(result.as<unaryop_expr_syntax *>());
    if (result.is<lval_syntax *>())
        return ptr<syntax_tree_node>(result.as<lval_syntax *>());
    if (result.is<literal_syntax *>())
        return ptr<syntax_tree_node>(result.as<literal_syntax *>());
    if (result.is<stmt_syntax *>())
        return ptr<syntax_tree_node>(result.as<stmt_syntax *>());
    if (result.is<var_def_stmt_syntax *>())
        return ptr<syntax_tree_node>(result.as<var_def_stmt_syntax *>());
    if (result.is<assign_stmt_syntax *>())
        return ptr<syntax_tree_node>(result.as<assign_stmt_syntax *>());
    if (result.is<func_call_stmt_syntax *>())
        return ptr<syntax_tree_node>(result.as<func_call_stmt_syntax *>());
    if (result.is<block_syntax *>())
        return ptr<syntax_tree_node>(result.as<block_syntax *>());
    if (result.is<if_stmt_syntax *>())
        return ptr<syntax_tree_node>(result.as<if_stmt_syntax *>());
    if (result.is<while_stmt_syntax *>())
        return ptr<syntax_tree_node>(result.as<while_stmt_syntax *>());
    return nullptr;
}
