
// Generated from /home/hyt/compile/lab4temp/c1recognizer/grammar/C1Parser.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "C1ParserListener.h"


/**
 * This class provides an empty implementation of C1ParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  C1ParserBaseListener : public C1ParserListener {
public:

  virtual void enterCompilationUnit(C1Parser::CompilationUnitContext * /*ctx*/) override { }
  virtual void exitCompilationUnit(C1Parser::CompilationUnitContext * /*ctx*/) override { }

  virtual void enterDecl(C1Parser::DeclContext * /*ctx*/) override { }
  virtual void exitDecl(C1Parser::DeclContext * /*ctx*/) override { }

  virtual void enterConstdecl(C1Parser::ConstdeclContext * /*ctx*/) override { }
  virtual void exitConstdecl(C1Parser::ConstdeclContext * /*ctx*/) override { }

  virtual void enterConstdef(C1Parser::ConstdefContext * /*ctx*/) override { }
  virtual void exitConstdef(C1Parser::ConstdefContext * /*ctx*/) override { }

  virtual void enterVardecl(C1Parser::VardeclContext * /*ctx*/) override { }
  virtual void exitVardecl(C1Parser::VardeclContext * /*ctx*/) override { }

  virtual void enterVardef(C1Parser::VardefContext * /*ctx*/) override { }
  virtual void exitVardef(C1Parser::VardefContext * /*ctx*/) override { }

  virtual void enterFuncdef(C1Parser::FuncdefContext * /*ctx*/) override { }
  virtual void exitFuncdef(C1Parser::FuncdefContext * /*ctx*/) override { }

  virtual void enterBlock(C1Parser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(C1Parser::BlockContext * /*ctx*/) override { }

  virtual void enterStmt(C1Parser::StmtContext * /*ctx*/) override { }
  virtual void exitStmt(C1Parser::StmtContext * /*ctx*/) override { }

  virtual void enterLval(C1Parser::LvalContext * /*ctx*/) override { }
  virtual void exitLval(C1Parser::LvalContext * /*ctx*/) override { }

  virtual void enterCond(C1Parser::CondContext * /*ctx*/) override { }
  virtual void exitCond(C1Parser::CondContext * /*ctx*/) override { }

  virtual void enterExp(C1Parser::ExpContext * /*ctx*/) override { }
  virtual void exitExp(C1Parser::ExpContext * /*ctx*/) override { }

  virtual void enterNumber(C1Parser::NumberContext * /*ctx*/) override { }
  virtual void exitNumber(C1Parser::NumberContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

