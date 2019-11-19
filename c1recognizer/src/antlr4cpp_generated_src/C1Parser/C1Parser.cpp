
// Generated from /home/hyt/compile/lab4temp/c1recognizer/grammar/C1Parser.g4 by ANTLR 4.7.2


#include "C1ParserListener.h"
#include "C1ParserVisitor.h"

#include "C1Parser.h"


using namespace antlrcpp;
using namespace antlr4;

C1Parser::C1Parser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

C1Parser::~C1Parser() {
  delete _interpreter;
}

std::string C1Parser::getGrammarFileName() const {
  return "C1Parser.g4";
}

const std::vector<std::string>& C1Parser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& C1Parser::getVocabulary() const {
  return _vocabulary;
}


//----------------- CompilationUnitContext ------------------------------------------------------------------

C1Parser::CompilationUnitContext::CompilationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C1Parser::CompilationUnitContext::EOF() {
  return getToken(C1Parser::EOF, 0);
}

std::vector<C1Parser::DeclContext *> C1Parser::CompilationUnitContext::decl() {
  return getRuleContexts<C1Parser::DeclContext>();
}

C1Parser::DeclContext* C1Parser::CompilationUnitContext::decl(size_t i) {
  return getRuleContext<C1Parser::DeclContext>(i);
}

std::vector<C1Parser::FuncdefContext *> C1Parser::CompilationUnitContext::funcdef() {
  return getRuleContexts<C1Parser::FuncdefContext>();
}

C1Parser::FuncdefContext* C1Parser::CompilationUnitContext::funcdef(size_t i) {
  return getRuleContext<C1Parser::FuncdefContext>(i);
}


size_t C1Parser::CompilationUnitContext::getRuleIndex() const {
  return C1Parser::RuleCompilationUnit;
}

void C1Parser::CompilationUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompilationUnit(this);
}

void C1Parser::CompilationUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompilationUnit(this);
}


antlrcpp::Any C1Parser::CompilationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor*>(visitor))
    return parserVisitor->visitCompilationUnit(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::CompilationUnitContext* C1Parser::compilationUnit() {
  CompilationUnitContext *_localctx = _tracker.createInstance<CompilationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, C1Parser::RuleCompilationUnit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(28); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(28);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case C1Parser::Const:
        case C1Parser::Int:
        case C1Parser::Float: {
          setState(26);
          decl();
          break;
        }

        case C1Parser::Void: {
          setState(27);
          funcdef();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(30); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C1Parser::Const)
      | (1ULL << C1Parser::Int)
      | (1ULL << C1Parser::Float)
      | (1ULL << C1Parser::Void))) != 0));
    setState(32);
    match(C1Parser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclContext ------------------------------------------------------------------

C1Parser::DeclContext::DeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C1Parser::ConstdeclContext* C1Parser::DeclContext::constdecl() {
  return getRuleContext<C1Parser::ConstdeclContext>(0);
}

C1Parser::VardeclContext* C1Parser::DeclContext::vardecl() {
  return getRuleContext<C1Parser::VardeclContext>(0);
}


size_t C1Parser::DeclContext::getRuleIndex() const {
  return C1Parser::RuleDecl;
}

void C1Parser::DeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDecl(this);
}

void C1Parser::DeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDecl(this);
}


antlrcpp::Any C1Parser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor*>(visitor))
    return parserVisitor->visitDecl(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::DeclContext* C1Parser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 2, C1Parser::RuleDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(36);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C1Parser::Const: {
        enterOuterAlt(_localctx, 1);
        setState(34);
        constdecl();
        break;
      }

      case C1Parser::Int:
      case C1Parser::Float: {
        enterOuterAlt(_localctx, 2);
        setState(35);
        vardecl();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstdeclContext ------------------------------------------------------------------

C1Parser::ConstdeclContext::ConstdeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C1Parser::ConstdeclContext::Const() {
  return getToken(C1Parser::Const, 0);
}

std::vector<C1Parser::ConstdefContext *> C1Parser::ConstdeclContext::constdef() {
  return getRuleContexts<C1Parser::ConstdefContext>();
}

C1Parser::ConstdefContext* C1Parser::ConstdeclContext::constdef(size_t i) {
  return getRuleContext<C1Parser::ConstdefContext>(i);
}

tree::TerminalNode* C1Parser::ConstdeclContext::SemiColon() {
  return getToken(C1Parser::SemiColon, 0);
}

tree::TerminalNode* C1Parser::ConstdeclContext::Int() {
  return getToken(C1Parser::Int, 0);
}

tree::TerminalNode* C1Parser::ConstdeclContext::Float() {
  return getToken(C1Parser::Float, 0);
}

std::vector<tree::TerminalNode *> C1Parser::ConstdeclContext::Comma() {
  return getTokens(C1Parser::Comma);
}

tree::TerminalNode* C1Parser::ConstdeclContext::Comma(size_t i) {
  return getToken(C1Parser::Comma, i);
}


size_t C1Parser::ConstdeclContext::getRuleIndex() const {
  return C1Parser::RuleConstdecl;
}

void C1Parser::ConstdeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstdecl(this);
}

void C1Parser::ConstdeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstdecl(this);
}


antlrcpp::Any C1Parser::ConstdeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor*>(visitor))
    return parserVisitor->visitConstdecl(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::ConstdeclContext* C1Parser::constdecl() {
  ConstdeclContext *_localctx = _tracker.createInstance<ConstdeclContext>(_ctx, getState());
  enterRule(_localctx, 4, C1Parser::RuleConstdecl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(38);
    match(C1Parser::Const);
    setState(39);
    _la = _input->LA(1);
    if (!(_la == C1Parser::Int

    || _la == C1Parser::Float)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(40);
    constdef();
    setState(45);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C1Parser::Comma) {
      setState(41);
      match(C1Parser::Comma);
      setState(42);
      constdef();
      setState(47);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(48);
    match(C1Parser::SemiColon);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstdefContext ------------------------------------------------------------------

C1Parser::ConstdefContext::ConstdefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C1Parser::ConstdefContext::Identifier() {
  return getToken(C1Parser::Identifier, 0);
}

tree::TerminalNode* C1Parser::ConstdefContext::Assign() {
  return getToken(C1Parser::Assign, 0);
}

std::vector<C1Parser::ExpContext *> C1Parser::ConstdefContext::exp() {
  return getRuleContexts<C1Parser::ExpContext>();
}

C1Parser::ExpContext* C1Parser::ConstdefContext::exp(size_t i) {
  return getRuleContext<C1Parser::ExpContext>(i);
}

tree::TerminalNode* C1Parser::ConstdefContext::LeftBracket() {
  return getToken(C1Parser::LeftBracket, 0);
}

tree::TerminalNode* C1Parser::ConstdefContext::RightBracket() {
  return getToken(C1Parser::RightBracket, 0);
}

tree::TerminalNode* C1Parser::ConstdefContext::LeftBrace() {
  return getToken(C1Parser::LeftBrace, 0);
}

tree::TerminalNode* C1Parser::ConstdefContext::RightBrace() {
  return getToken(C1Parser::RightBrace, 0);
}

std::vector<tree::TerminalNode *> C1Parser::ConstdefContext::Comma() {
  return getTokens(C1Parser::Comma);
}

tree::TerminalNode* C1Parser::ConstdefContext::Comma(size_t i) {
  return getToken(C1Parser::Comma, i);
}


size_t C1Parser::ConstdefContext::getRuleIndex() const {
  return C1Parser::RuleConstdef;
}

void C1Parser::ConstdefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstdef(this);
}

void C1Parser::ConstdefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstdef(this);
}


antlrcpp::Any C1Parser::ConstdefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor*>(visitor))
    return parserVisitor->visitConstdef(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::ConstdefContext* C1Parser::constdef() {
  ConstdefContext *_localctx = _tracker.createInstance<ConstdefContext>(_ctx, getState());
  enterRule(_localctx, 6, C1Parser::RuleConstdef);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(71);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(50);
      match(C1Parser::Identifier);
      setState(51);
      match(C1Parser::Assign);
      setState(52);
      exp(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(53);
      match(C1Parser::Identifier);
      setState(54);
      match(C1Parser::LeftBracket);
      setState(56);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << C1Parser::LeftParen)
        | (1ULL << C1Parser::Plus)
        | (1ULL << C1Parser::Minus)
        | (1ULL << C1Parser::Identifier)
        | (1ULL << C1Parser::FloatConst)
        | (1ULL << C1Parser::IntConst))) != 0)) {
        setState(55);
        exp(0);
      }
      setState(58);
      match(C1Parser::RightBracket);
      setState(59);
      match(C1Parser::Assign);
      setState(60);
      match(C1Parser::LeftBrace);
      setState(61);
      exp(0);
      setState(66);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == C1Parser::Comma) {
        setState(62);
        match(C1Parser::Comma);
        setState(63);
        exp(0);
        setState(68);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(69);
      match(C1Parser::RightBrace);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VardeclContext ------------------------------------------------------------------

C1Parser::VardeclContext::VardeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C1Parser::VardefContext *> C1Parser::VardeclContext::vardef() {
  return getRuleContexts<C1Parser::VardefContext>();
}

C1Parser::VardefContext* C1Parser::VardeclContext::vardef(size_t i) {
  return getRuleContext<C1Parser::VardefContext>(i);
}

tree::TerminalNode* C1Parser::VardeclContext::SemiColon() {
  return getToken(C1Parser::SemiColon, 0);
}

tree::TerminalNode* C1Parser::VardeclContext::Int() {
  return getToken(C1Parser::Int, 0);
}

tree::TerminalNode* C1Parser::VardeclContext::Float() {
  return getToken(C1Parser::Float, 0);
}

std::vector<tree::TerminalNode *> C1Parser::VardeclContext::Comma() {
  return getTokens(C1Parser::Comma);
}

tree::TerminalNode* C1Parser::VardeclContext::Comma(size_t i) {
  return getToken(C1Parser::Comma, i);
}


size_t C1Parser::VardeclContext::getRuleIndex() const {
  return C1Parser::RuleVardecl;
}

void C1Parser::VardeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVardecl(this);
}

void C1Parser::VardeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVardecl(this);
}


antlrcpp::Any C1Parser::VardeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor*>(visitor))
    return parserVisitor->visitVardecl(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::VardeclContext* C1Parser::vardecl() {
  VardeclContext *_localctx = _tracker.createInstance<VardeclContext>(_ctx, getState());
  enterRule(_localctx, 8, C1Parser::RuleVardecl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(73);
    _la = _input->LA(1);
    if (!(_la == C1Parser::Int

    || _la == C1Parser::Float)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(74);
    vardef();
    setState(79);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C1Parser::Comma) {
      setState(75);
      match(C1Parser::Comma);
      setState(76);
      vardef();
      setState(81);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(82);
    match(C1Parser::SemiColon);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VardefContext ------------------------------------------------------------------

C1Parser::VardefContext::VardefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C1Parser::VardefContext::Identifier() {
  return getToken(C1Parser::Identifier, 0);
}

tree::TerminalNode* C1Parser::VardefContext::LeftBracket() {
  return getToken(C1Parser::LeftBracket, 0);
}

std::vector<C1Parser::ExpContext *> C1Parser::VardefContext::exp() {
  return getRuleContexts<C1Parser::ExpContext>();
}

C1Parser::ExpContext* C1Parser::VardefContext::exp(size_t i) {
  return getRuleContext<C1Parser::ExpContext>(i);
}

tree::TerminalNode* C1Parser::VardefContext::RightBracket() {
  return getToken(C1Parser::RightBracket, 0);
}

tree::TerminalNode* C1Parser::VardefContext::Assign() {
  return getToken(C1Parser::Assign, 0);
}

tree::TerminalNode* C1Parser::VardefContext::LeftBrace() {
  return getToken(C1Parser::LeftBrace, 0);
}

tree::TerminalNode* C1Parser::VardefContext::RightBrace() {
  return getToken(C1Parser::RightBrace, 0);
}

std::vector<tree::TerminalNode *> C1Parser::VardefContext::Comma() {
  return getTokens(C1Parser::Comma);
}

tree::TerminalNode* C1Parser::VardefContext::Comma(size_t i) {
  return getToken(C1Parser::Comma, i);
}


size_t C1Parser::VardefContext::getRuleIndex() const {
  return C1Parser::RuleVardef;
}

void C1Parser::VardefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVardef(this);
}

void C1Parser::VardefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVardef(this);
}


antlrcpp::Any C1Parser::VardefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor*>(visitor))
    return parserVisitor->visitVardef(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::VardefContext* C1Parser::vardef() {
  VardefContext *_localctx = _tracker.createInstance<VardefContext>(_ctx, getState());
  enterRule(_localctx, 10, C1Parser::RuleVardef);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(111);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(84);
      match(C1Parser::Identifier);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(85);
      match(C1Parser::Identifier);
      setState(86);
      match(C1Parser::LeftBracket);
      setState(87);
      exp(0);
      setState(88);
      match(C1Parser::RightBracket);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(90);
      match(C1Parser::Identifier);
      setState(91);
      match(C1Parser::Assign);
      setState(92);
      exp(0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(93);
      match(C1Parser::Identifier);
      setState(94);
      match(C1Parser::LeftBracket);
      setState(96);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << C1Parser::LeftParen)
        | (1ULL << C1Parser::Plus)
        | (1ULL << C1Parser::Minus)
        | (1ULL << C1Parser::Identifier)
        | (1ULL << C1Parser::FloatConst)
        | (1ULL << C1Parser::IntConst))) != 0)) {
        setState(95);
        exp(0);
      }
      setState(98);
      match(C1Parser::RightBracket);
      setState(99);
      match(C1Parser::Assign);
      setState(100);
      match(C1Parser::LeftBrace);
      setState(101);
      exp(0);
      setState(106);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == C1Parser::Comma) {
        setState(102);
        match(C1Parser::Comma);
        setState(103);
        exp(0);
        setState(108);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(109);
      match(C1Parser::RightBrace);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncdefContext ------------------------------------------------------------------

C1Parser::FuncdefContext::FuncdefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C1Parser::FuncdefContext::Void() {
  return getToken(C1Parser::Void, 0);
}

tree::TerminalNode* C1Parser::FuncdefContext::Identifier() {
  return getToken(C1Parser::Identifier, 0);
}

tree::TerminalNode* C1Parser::FuncdefContext::LeftParen() {
  return getToken(C1Parser::LeftParen, 0);
}

tree::TerminalNode* C1Parser::FuncdefContext::RightParen() {
  return getToken(C1Parser::RightParen, 0);
}

C1Parser::BlockContext* C1Parser::FuncdefContext::block() {
  return getRuleContext<C1Parser::BlockContext>(0);
}


size_t C1Parser::FuncdefContext::getRuleIndex() const {
  return C1Parser::RuleFuncdef;
}

void C1Parser::FuncdefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncdef(this);
}

void C1Parser::FuncdefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncdef(this);
}


antlrcpp::Any C1Parser::FuncdefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor*>(visitor))
    return parserVisitor->visitFuncdef(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::FuncdefContext* C1Parser::funcdef() {
  FuncdefContext *_localctx = _tracker.createInstance<FuncdefContext>(_ctx, getState());
  enterRule(_localctx, 12, C1Parser::RuleFuncdef);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(113);
    match(C1Parser::Void);
    setState(114);
    match(C1Parser::Identifier);
    setState(115);
    match(C1Parser::LeftParen);
    setState(116);
    match(C1Parser::RightParen);
    setState(117);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

C1Parser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C1Parser::BlockContext::LeftBrace() {
  return getToken(C1Parser::LeftBrace, 0);
}

tree::TerminalNode* C1Parser::BlockContext::RightBrace() {
  return getToken(C1Parser::RightBrace, 0);
}

std::vector<C1Parser::DeclContext *> C1Parser::BlockContext::decl() {
  return getRuleContexts<C1Parser::DeclContext>();
}

C1Parser::DeclContext* C1Parser::BlockContext::decl(size_t i) {
  return getRuleContext<C1Parser::DeclContext>(i);
}

std::vector<C1Parser::StmtContext *> C1Parser::BlockContext::stmt() {
  return getRuleContexts<C1Parser::StmtContext>();
}

C1Parser::StmtContext* C1Parser::BlockContext::stmt(size_t i) {
  return getRuleContext<C1Parser::StmtContext>(i);
}


size_t C1Parser::BlockContext::getRuleIndex() const {
  return C1Parser::RuleBlock;
}

void C1Parser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void C1Parser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


antlrcpp::Any C1Parser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::BlockContext* C1Parser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 14, C1Parser::RuleBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(119);
    match(C1Parser::LeftBrace);
    setState(124);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C1Parser::SemiColon)
      | (1ULL << C1Parser::LeftBrace)
      | (1ULL << C1Parser::If)
      | (1ULL << C1Parser::While)
      | (1ULL << C1Parser::Const)
      | (1ULL << C1Parser::Int)
      | (1ULL << C1Parser::Float)
      | (1ULL << C1Parser::Identifier))) != 0)) {
      setState(122);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case C1Parser::Const:
        case C1Parser::Int:
        case C1Parser::Float: {
          setState(120);
          decl();
          break;
        }

        case C1Parser::SemiColon:
        case C1Parser::LeftBrace:
        case C1Parser::If:
        case C1Parser::While:
        case C1Parser::Identifier: {
          setState(121);
          stmt();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(126);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(127);
    match(C1Parser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

C1Parser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C1Parser::LvalContext* C1Parser::StmtContext::lval() {
  return getRuleContext<C1Parser::LvalContext>(0);
}

tree::TerminalNode* C1Parser::StmtContext::Assign() {
  return getToken(C1Parser::Assign, 0);
}

C1Parser::ExpContext* C1Parser::StmtContext::exp() {
  return getRuleContext<C1Parser::ExpContext>(0);
}

tree::TerminalNode* C1Parser::StmtContext::SemiColon() {
  return getToken(C1Parser::SemiColon, 0);
}

tree::TerminalNode* C1Parser::StmtContext::Identifier() {
  return getToken(C1Parser::Identifier, 0);
}

tree::TerminalNode* C1Parser::StmtContext::LeftParen() {
  return getToken(C1Parser::LeftParen, 0);
}

tree::TerminalNode* C1Parser::StmtContext::RightParen() {
  return getToken(C1Parser::RightParen, 0);
}

C1Parser::BlockContext* C1Parser::StmtContext::block() {
  return getRuleContext<C1Parser::BlockContext>(0);
}

tree::TerminalNode* C1Parser::StmtContext::If() {
  return getToken(C1Parser::If, 0);
}

C1Parser::CondContext* C1Parser::StmtContext::cond() {
  return getRuleContext<C1Parser::CondContext>(0);
}

std::vector<C1Parser::StmtContext *> C1Parser::StmtContext::stmt() {
  return getRuleContexts<C1Parser::StmtContext>();
}

C1Parser::StmtContext* C1Parser::StmtContext::stmt(size_t i) {
  return getRuleContext<C1Parser::StmtContext>(i);
}

tree::TerminalNode* C1Parser::StmtContext::Else() {
  return getToken(C1Parser::Else, 0);
}

tree::TerminalNode* C1Parser::StmtContext::While() {
  return getToken(C1Parser::While, 0);
}


size_t C1Parser::StmtContext::getRuleIndex() const {
  return C1Parser::RuleStmt;
}

void C1Parser::StmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt(this);
}

void C1Parser::StmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt(this);
}


antlrcpp::Any C1Parser::StmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor*>(visitor))
    return parserVisitor->visitStmt(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::StmtContext* C1Parser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 16, C1Parser::RuleStmt);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(155);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(129);
      lval();
      setState(130);
      match(C1Parser::Assign);
      setState(131);
      exp(0);
      setState(132);
      match(C1Parser::SemiColon);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(134);
      match(C1Parser::Identifier);
      setState(135);
      match(C1Parser::LeftParen);
      setState(136);
      match(C1Parser::RightParen);
      setState(137);
      match(C1Parser::SemiColon);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(138);
      block();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(139);
      match(C1Parser::If);
      setState(140);
      match(C1Parser::LeftParen);
      setState(141);
      cond();
      setState(142);
      match(C1Parser::RightParen);
      setState(143);
      stmt();
      setState(146);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
      case 1: {
        setState(144);
        match(C1Parser::Else);
        setState(145);
        stmt();
        break;
      }

      }
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(148);
      match(C1Parser::While);
      setState(149);
      match(C1Parser::LeftParen);
      setState(150);
      cond();
      setState(151);
      match(C1Parser::RightParen);
      setState(152);
      stmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(154);
      match(C1Parser::SemiColon);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LvalContext ------------------------------------------------------------------

C1Parser::LvalContext::LvalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C1Parser::LvalContext::Identifier() {
  return getToken(C1Parser::Identifier, 0);
}

tree::TerminalNode* C1Parser::LvalContext::LeftBracket() {
  return getToken(C1Parser::LeftBracket, 0);
}

C1Parser::ExpContext* C1Parser::LvalContext::exp() {
  return getRuleContext<C1Parser::ExpContext>(0);
}

tree::TerminalNode* C1Parser::LvalContext::RightBracket() {
  return getToken(C1Parser::RightBracket, 0);
}


size_t C1Parser::LvalContext::getRuleIndex() const {
  return C1Parser::RuleLval;
}

void C1Parser::LvalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLval(this);
}

void C1Parser::LvalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLval(this);
}


antlrcpp::Any C1Parser::LvalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor*>(visitor))
    return parserVisitor->visitLval(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::LvalContext* C1Parser::lval() {
  LvalContext *_localctx = _tracker.createInstance<LvalContext>(_ctx, getState());
  enterRule(_localctx, 18, C1Parser::RuleLval);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(163);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(157);
      match(C1Parser::Identifier);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(158);
      match(C1Parser::Identifier);
      setState(159);
      match(C1Parser::LeftBracket);
      setState(160);
      exp(0);
      setState(161);
      match(C1Parser::RightBracket);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CondContext ------------------------------------------------------------------

C1Parser::CondContext::CondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C1Parser::ExpContext *> C1Parser::CondContext::exp() {
  return getRuleContexts<C1Parser::ExpContext>();
}

C1Parser::ExpContext* C1Parser::CondContext::exp(size_t i) {
  return getRuleContext<C1Parser::ExpContext>(i);
}

tree::TerminalNode* C1Parser::CondContext::Equal() {
  return getToken(C1Parser::Equal, 0);
}

tree::TerminalNode* C1Parser::CondContext::NonEqual() {
  return getToken(C1Parser::NonEqual, 0);
}

tree::TerminalNode* C1Parser::CondContext::Less() {
  return getToken(C1Parser::Less, 0);
}

tree::TerminalNode* C1Parser::CondContext::LessEqual() {
  return getToken(C1Parser::LessEqual, 0);
}

tree::TerminalNode* C1Parser::CondContext::Greater() {
  return getToken(C1Parser::Greater, 0);
}

tree::TerminalNode* C1Parser::CondContext::GreaterEqual() {
  return getToken(C1Parser::GreaterEqual, 0);
}


size_t C1Parser::CondContext::getRuleIndex() const {
  return C1Parser::RuleCond;
}

void C1Parser::CondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCond(this);
}

void C1Parser::CondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCond(this);
}


antlrcpp::Any C1Parser::CondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor*>(visitor))
    return parserVisitor->visitCond(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::CondContext* C1Parser::cond() {
  CondContext *_localctx = _tracker.createInstance<CondContext>(_ctx, getState());
  enterRule(_localctx, 20, C1Parser::RuleCond);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(165);
    exp(0);
    setState(166);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C1Parser::Equal)
      | (1ULL << C1Parser::NonEqual)
      | (1ULL << C1Parser::Less)
      | (1ULL << C1Parser::Greater)
      | (1ULL << C1Parser::LessEqual)
      | (1ULL << C1Parser::GreaterEqual))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(167);
    exp(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

C1Parser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C1Parser::ExpContext *> C1Parser::ExpContext::exp() {
  return getRuleContexts<C1Parser::ExpContext>();
}

C1Parser::ExpContext* C1Parser::ExpContext::exp(size_t i) {
  return getRuleContext<C1Parser::ExpContext>(i);
}

tree::TerminalNode* C1Parser::ExpContext::Plus() {
  return getToken(C1Parser::Plus, 0);
}

tree::TerminalNode* C1Parser::ExpContext::Minus() {
  return getToken(C1Parser::Minus, 0);
}

tree::TerminalNode* C1Parser::ExpContext::LeftParen() {
  return getToken(C1Parser::LeftParen, 0);
}

tree::TerminalNode* C1Parser::ExpContext::RightParen() {
  return getToken(C1Parser::RightParen, 0);
}

C1Parser::LvalContext* C1Parser::ExpContext::lval() {
  return getRuleContext<C1Parser::LvalContext>(0);
}

C1Parser::NumberContext* C1Parser::ExpContext::number() {
  return getRuleContext<C1Parser::NumberContext>(0);
}

tree::TerminalNode* C1Parser::ExpContext::Multiply() {
  return getToken(C1Parser::Multiply, 0);
}

tree::TerminalNode* C1Parser::ExpContext::Divide() {
  return getToken(C1Parser::Divide, 0);
}

tree::TerminalNode* C1Parser::ExpContext::Modulo() {
  return getToken(C1Parser::Modulo, 0);
}


size_t C1Parser::ExpContext::getRuleIndex() const {
  return C1Parser::RuleExp;
}

void C1Parser::ExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExp(this);
}

void C1Parser::ExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExp(this);
}


antlrcpp::Any C1Parser::ExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor*>(visitor))
    return parserVisitor->visitExp(this);
  else
    return visitor->visitChildren(this);
}


C1Parser::ExpContext* C1Parser::exp() {
   return exp(0);
}

C1Parser::ExpContext* C1Parser::exp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C1Parser::ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, parentState);
  C1Parser::ExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 22;
  enterRecursionRule(_localctx, 22, C1Parser::RuleExp, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(178);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C1Parser::Plus:
      case C1Parser::Minus: {
        setState(170);
        _la = _input->LA(1);
        if (!(_la == C1Parser::Plus

        || _la == C1Parser::Minus)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(171);
        exp(6);
        break;
      }

      case C1Parser::LeftParen: {
        setState(172);
        match(C1Parser::LeftParen);
        setState(173);
        exp(0);
        setState(174);
        match(C1Parser::RightParen);
        break;
      }

      case C1Parser::Identifier: {
        setState(176);
        lval();
        break;
      }

      case C1Parser::FloatConst:
      case C1Parser::IntConst: {
        setState(177);
        number();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(188);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(186);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExp);
          setState(180);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(181);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << C1Parser::Multiply)
            | (1ULL << C1Parser::Divide)
            | (1ULL << C1Parser::Modulo))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(182);
          exp(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExp);
          setState(183);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(184);
          _la = _input->LA(1);
          if (!(_la == C1Parser::Plus

          || _la == C1Parser::Minus)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(185);
          exp(5);
          break;
        }

        } 
      }
      setState(190);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

C1Parser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C1Parser::NumberContext::FloatConst() {
  return getToken(C1Parser::FloatConst, 0);
}

tree::TerminalNode* C1Parser::NumberContext::IntConst() {
  return getToken(C1Parser::IntConst, 0);
}


size_t C1Parser::NumberContext::getRuleIndex() const {
  return C1Parser::RuleNumber;
}

void C1Parser::NumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber(this);
}

void C1Parser::NumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber(this);
}


antlrcpp::Any C1Parser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::NumberContext* C1Parser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 24, C1Parser::RuleNumber);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(191);
    _la = _input->LA(1);
    if (!(_la == C1Parser::FloatConst

    || _la == C1Parser::IntConst)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool C1Parser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 11: return expSempred(dynamic_cast<ExpContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool C1Parser::expSempred(ExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 5);
    case 1: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> C1Parser::_decisionToDFA;
atn::PredictionContextCache C1Parser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN C1Parser::_atn;
std::vector<uint16_t> C1Parser::_serializedATN;

std::vector<std::string> C1Parser::_ruleNames = {
  "compilationUnit", "decl", "constdecl", "constdef", "vardecl", "vardef", 
  "funcdef", "block", "stmt", "lval", "cond", "exp", "number"
};

std::vector<std::string> C1Parser::_literalNames = {
  "", "','", "';'", "'='", "'['", "']'", "'{'", "'}'", "'('", "')'", "'if'", 
  "'else'", "'while'", "'const'", "'=='", "'!='", "'<'", "'>'", "'<='", 
  "'>='", "'+'", "'-'", "'*'", "'/'", "'%'", "'int'", "'float'", "'void'"
};

std::vector<std::string> C1Parser::_symbolicNames = {
  "", "Comma", "SemiColon", "Assign", "LeftBracket", "RightBracket", "LeftBrace", 
  "RightBrace", "LeftParen", "RightParen", "If", "Else", "While", "Const", 
  "Equal", "NonEqual", "Less", "Greater", "LessEqual", "GreaterEqual", "Plus", 
  "Minus", "Multiply", "Divide", "Modulo", "Int", "Float", "Void", "Identifier", 
  "FloatConst", "IntConst", "LineComment", "BlockComment", "WhiteSpace"
};

dfa::Vocabulary C1Parser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> C1Parser::_tokenNames;

C1Parser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x23, 0xc4, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x3, 
    0x2, 0x3, 0x2, 0x6, 0x2, 0x1f, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x20, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x27, 0xa, 0x3, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x2e, 0xa, 0x4, 0xc, 
    0x4, 0xe, 0x4, 0x31, 0xb, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x3b, 0xa, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x43, 
    0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x46, 0xb, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 
    0x5, 0x4a, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 
    0x50, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x53, 0xb, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x63, 0xa, 
    0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 
    0x7, 0x6b, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x6e, 0xb, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x5, 0x7, 0x72, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0x7d, 0xa, 
    0x9, 0xc, 0x9, 0xe, 0x9, 0x80, 0xb, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x95, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x9e, 0xa, 0xa, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 
    0xa6, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x5, 0xd, 0xb5, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x7, 0xd, 0xbd, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0xc0, 
    0xb, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x2, 0x3, 0x18, 0xf, 0x2, 0x4, 
    0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x2, 0x7, 
    0x3, 0x2, 0x1b, 0x1c, 0x3, 0x2, 0x10, 0x15, 0x3, 0x2, 0x16, 0x17, 0x3, 
    0x2, 0x18, 0x1a, 0x3, 0x2, 0x1f, 0x20, 0x2, 0xd1, 0x2, 0x1e, 0x3, 0x2, 
    0x2, 0x2, 0x4, 0x26, 0x3, 0x2, 0x2, 0x2, 0x6, 0x28, 0x3, 0x2, 0x2, 0x2, 
    0x8, 0x49, 0x3, 0x2, 0x2, 0x2, 0xa, 0x4b, 0x3, 0x2, 0x2, 0x2, 0xc, 0x71, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x73, 0x3, 0x2, 0x2, 0x2, 0x10, 0x79, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x14, 0xa5, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0xa7, 0x3, 0x2, 0x2, 0x2, 0x18, 0xb4, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0xc1, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1f, 0x5, 0x4, 0x3, 0x2, 
    0x1d, 0x1f, 0x5, 0xe, 0x8, 0x2, 0x1e, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x1e, 
    0x1d, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x20, 0x3, 0x2, 0x2, 0x2, 0x20, 0x1e, 
    0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 0x3, 0x2, 0x2, 0x2, 0x21, 0x22, 0x3, 
    0x2, 0x2, 0x2, 0x22, 0x23, 0x7, 0x2, 0x2, 0x3, 0x23, 0x3, 0x3, 0x2, 
    0x2, 0x2, 0x24, 0x27, 0x5, 0x6, 0x4, 0x2, 0x25, 0x27, 0x5, 0xa, 0x6, 
    0x2, 0x26, 0x24, 0x3, 0x2, 0x2, 0x2, 0x26, 0x25, 0x3, 0x2, 0x2, 0x2, 
    0x27, 0x5, 0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 0x7, 0xf, 0x2, 0x2, 0x29, 
    0x2a, 0x9, 0x2, 0x2, 0x2, 0x2a, 0x2f, 0x5, 0x8, 0x5, 0x2, 0x2b, 0x2c, 
    0x7, 0x3, 0x2, 0x2, 0x2c, 0x2e, 0x5, 0x8, 0x5, 0x2, 0x2d, 0x2b, 0x3, 
    0x2, 0x2, 0x2, 0x2e, 0x31, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x2d, 0x3, 0x2, 
    0x2, 0x2, 0x2f, 0x30, 0x3, 0x2, 0x2, 0x2, 0x30, 0x32, 0x3, 0x2, 0x2, 
    0x2, 0x31, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x32, 0x33, 0x7, 0x4, 0x2, 0x2, 
    0x33, 0x7, 0x3, 0x2, 0x2, 0x2, 0x34, 0x35, 0x7, 0x1e, 0x2, 0x2, 0x35, 
    0x36, 0x7, 0x5, 0x2, 0x2, 0x36, 0x4a, 0x5, 0x18, 0xd, 0x2, 0x37, 0x38, 
    0x7, 0x1e, 0x2, 0x2, 0x38, 0x3a, 0x7, 0x6, 0x2, 0x2, 0x39, 0x3b, 0x5, 
    0x18, 0xd, 0x2, 0x3a, 0x39, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3b, 0x3, 0x2, 
    0x2, 0x2, 0x3b, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3d, 0x7, 0x7, 0x2, 
    0x2, 0x3d, 0x3e, 0x7, 0x5, 0x2, 0x2, 0x3e, 0x3f, 0x7, 0x8, 0x2, 0x2, 
    0x3f, 0x44, 0x5, 0x18, 0xd, 0x2, 0x40, 0x41, 0x7, 0x3, 0x2, 0x2, 0x41, 
    0x43, 0x5, 0x18, 0xd, 0x2, 0x42, 0x40, 0x3, 0x2, 0x2, 0x2, 0x43, 0x46, 
    0x3, 0x2, 0x2, 0x2, 0x44, 0x42, 0x3, 0x2, 0x2, 0x2, 0x44, 0x45, 0x3, 
    0x2, 0x2, 0x2, 0x45, 0x47, 0x3, 0x2, 0x2, 0x2, 0x46, 0x44, 0x3, 0x2, 
    0x2, 0x2, 0x47, 0x48, 0x7, 0x9, 0x2, 0x2, 0x48, 0x4a, 0x3, 0x2, 0x2, 
    0x2, 0x49, 0x34, 0x3, 0x2, 0x2, 0x2, 0x49, 0x37, 0x3, 0x2, 0x2, 0x2, 
    0x4a, 0x9, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 0x9, 0x2, 0x2, 0x2, 0x4c, 
    0x51, 0x5, 0xc, 0x7, 0x2, 0x4d, 0x4e, 0x7, 0x3, 0x2, 0x2, 0x4e, 0x50, 
    0x5, 0xc, 0x7, 0x2, 0x4f, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x50, 0x53, 0x3, 
    0x2, 0x2, 0x2, 0x51, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x3, 0x2, 
    0x2, 0x2, 0x52, 0x54, 0x3, 0x2, 0x2, 0x2, 0x53, 0x51, 0x3, 0x2, 0x2, 
    0x2, 0x54, 0x55, 0x7, 0x4, 0x2, 0x2, 0x55, 0xb, 0x3, 0x2, 0x2, 0x2, 
    0x56, 0x72, 0x7, 0x1e, 0x2, 0x2, 0x57, 0x58, 0x7, 0x1e, 0x2, 0x2, 0x58, 
    0x59, 0x7, 0x6, 0x2, 0x2, 0x59, 0x5a, 0x5, 0x18, 0xd, 0x2, 0x5a, 0x5b, 
    0x7, 0x7, 0x2, 0x2, 0x5b, 0x72, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 0x7, 
    0x1e, 0x2, 0x2, 0x5d, 0x5e, 0x7, 0x5, 0x2, 0x2, 0x5e, 0x72, 0x5, 0x18, 
    0xd, 0x2, 0x5f, 0x60, 0x7, 0x1e, 0x2, 0x2, 0x60, 0x62, 0x7, 0x6, 0x2, 
    0x2, 0x61, 0x63, 0x5, 0x18, 0xd, 0x2, 0x62, 0x61, 0x3, 0x2, 0x2, 0x2, 
    0x62, 0x63, 0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x3, 0x2, 0x2, 0x2, 0x64, 
    0x65, 0x7, 0x7, 0x2, 0x2, 0x65, 0x66, 0x7, 0x5, 0x2, 0x2, 0x66, 0x67, 
    0x7, 0x8, 0x2, 0x2, 0x67, 0x6c, 0x5, 0x18, 0xd, 0x2, 0x68, 0x69, 0x7, 
    0x3, 0x2, 0x2, 0x69, 0x6b, 0x5, 0x18, 0xd, 0x2, 0x6a, 0x68, 0x3, 0x2, 
    0x2, 0x2, 0x6b, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6a, 0x3, 0x2, 0x2, 
    0x2, 0x6c, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6f, 0x3, 0x2, 0x2, 0x2, 
    0x6e, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 0x7, 0x9, 0x2, 0x2, 0x70, 
    0x72, 0x3, 0x2, 0x2, 0x2, 0x71, 0x56, 0x3, 0x2, 0x2, 0x2, 0x71, 0x57, 
    0x3, 0x2, 0x2, 0x2, 0x71, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x71, 0x5f, 0x3, 
    0x2, 0x2, 0x2, 0x72, 0xd, 0x3, 0x2, 0x2, 0x2, 0x73, 0x74, 0x7, 0x1d, 
    0x2, 0x2, 0x74, 0x75, 0x7, 0x1e, 0x2, 0x2, 0x75, 0x76, 0x7, 0xa, 0x2, 
    0x2, 0x76, 0x77, 0x7, 0xb, 0x2, 0x2, 0x77, 0x78, 0x5, 0x10, 0x9, 0x2, 
    0x78, 0xf, 0x3, 0x2, 0x2, 0x2, 0x79, 0x7e, 0x7, 0x8, 0x2, 0x2, 0x7a, 
    0x7d, 0x5, 0x4, 0x3, 0x2, 0x7b, 0x7d, 0x5, 0x12, 0xa, 0x2, 0x7c, 0x7a, 
    0x3, 0x2, 0x2, 0x2, 0x7c, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x80, 0x3, 
    0x2, 0x2, 0x2, 0x7e, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x7f, 0x3, 0x2, 
    0x2, 0x2, 0x7f, 0x81, 0x3, 0x2, 0x2, 0x2, 0x80, 0x7e, 0x3, 0x2, 0x2, 
    0x2, 0x81, 0x82, 0x7, 0x9, 0x2, 0x2, 0x82, 0x11, 0x3, 0x2, 0x2, 0x2, 
    0x83, 0x84, 0x5, 0x14, 0xb, 0x2, 0x84, 0x85, 0x7, 0x5, 0x2, 0x2, 0x85, 
    0x86, 0x5, 0x18, 0xd, 0x2, 0x86, 0x87, 0x7, 0x4, 0x2, 0x2, 0x87, 0x9e, 
    0x3, 0x2, 0x2, 0x2, 0x88, 0x89, 0x7, 0x1e, 0x2, 0x2, 0x89, 0x8a, 0x7, 
    0xa, 0x2, 0x2, 0x8a, 0x8b, 0x7, 0xb, 0x2, 0x2, 0x8b, 0x9e, 0x7, 0x4, 
    0x2, 0x2, 0x8c, 0x9e, 0x5, 0x10, 0x9, 0x2, 0x8d, 0x8e, 0x7, 0xc, 0x2, 
    0x2, 0x8e, 0x8f, 0x7, 0xa, 0x2, 0x2, 0x8f, 0x90, 0x5, 0x16, 0xc, 0x2, 
    0x90, 0x91, 0x7, 0xb, 0x2, 0x2, 0x91, 0x94, 0x5, 0x12, 0xa, 0x2, 0x92, 
    0x93, 0x7, 0xd, 0x2, 0x2, 0x93, 0x95, 0x5, 0x12, 0xa, 0x2, 0x94, 0x92, 
    0x3, 0x2, 0x2, 0x2, 0x94, 0x95, 0x3, 0x2, 0x2, 0x2, 0x95, 0x9e, 0x3, 
    0x2, 0x2, 0x2, 0x96, 0x97, 0x7, 0xe, 0x2, 0x2, 0x97, 0x98, 0x7, 0xa, 
    0x2, 0x2, 0x98, 0x99, 0x5, 0x16, 0xc, 0x2, 0x99, 0x9a, 0x7, 0xb, 0x2, 
    0x2, 0x9a, 0x9b, 0x5, 0x12, 0xa, 0x2, 0x9b, 0x9e, 0x3, 0x2, 0x2, 0x2, 
    0x9c, 0x9e, 0x7, 0x4, 0x2, 0x2, 0x9d, 0x83, 0x3, 0x2, 0x2, 0x2, 0x9d, 
    0x88, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x8d, 
    0x3, 0x2, 0x2, 0x2, 0x9d, 0x96, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x9c, 0x3, 
    0x2, 0x2, 0x2, 0x9e, 0x13, 0x3, 0x2, 0x2, 0x2, 0x9f, 0xa6, 0x7, 0x1e, 
    0x2, 0x2, 0xa0, 0xa1, 0x7, 0x1e, 0x2, 0x2, 0xa1, 0xa2, 0x7, 0x6, 0x2, 
    0x2, 0xa2, 0xa3, 0x5, 0x18, 0xd, 0x2, 0xa3, 0xa4, 0x7, 0x7, 0x2, 0x2, 
    0xa4, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xa5, 0x9f, 0x3, 0x2, 0x2, 0x2, 0xa5, 
    0xa0, 0x3, 0x2, 0x2, 0x2, 0xa6, 0x15, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xa8, 
    0x5, 0x18, 0xd, 0x2, 0xa8, 0xa9, 0x9, 0x3, 0x2, 0x2, 0xa9, 0xaa, 0x5, 
    0x18, 0xd, 0x2, 0xaa, 0x17, 0x3, 0x2, 0x2, 0x2, 0xab, 0xac, 0x8, 0xd, 
    0x1, 0x2, 0xac, 0xad, 0x9, 0x4, 0x2, 0x2, 0xad, 0xb5, 0x5, 0x18, 0xd, 
    0x8, 0xae, 0xaf, 0x7, 0xa, 0x2, 0x2, 0xaf, 0xb0, 0x5, 0x18, 0xd, 0x2, 
    0xb0, 0xb1, 0x7, 0xb, 0x2, 0x2, 0xb1, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xb2, 
    0xb5, 0x5, 0x14, 0xb, 0x2, 0xb3, 0xb5, 0x5, 0x1a, 0xe, 0x2, 0xb4, 0xab, 
    0x3, 0x2, 0x2, 0x2, 0xb4, 0xae, 0x3, 0x2, 0x2, 0x2, 0xb4, 0xb2, 0x3, 
    0x2, 0x2, 0x2, 0xb4, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xbe, 0x3, 0x2, 
    0x2, 0x2, 0xb6, 0xb7, 0xc, 0x7, 0x2, 0x2, 0xb7, 0xb8, 0x9, 0x5, 0x2, 
    0x2, 0xb8, 0xbd, 0x5, 0x18, 0xd, 0x8, 0xb9, 0xba, 0xc, 0x6, 0x2, 0x2, 
    0xba, 0xbb, 0x9, 0x4, 0x2, 0x2, 0xbb, 0xbd, 0x5, 0x18, 0xd, 0x7, 0xbc, 
    0xb6, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xb9, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xc0, 
    0x3, 0x2, 0x2, 0x2, 0xbe, 0xbc, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xbf, 0x3, 
    0x2, 0x2, 0x2, 0xbf, 0x19, 0x3, 0x2, 0x2, 0x2, 0xc0, 0xbe, 0x3, 0x2, 
    0x2, 0x2, 0xc1, 0xc2, 0x9, 0x6, 0x2, 0x2, 0xc2, 0x1b, 0x3, 0x2, 0x2, 
    0x2, 0x15, 0x1e, 0x20, 0x26, 0x2f, 0x3a, 0x44, 0x49, 0x51, 0x62, 0x6c, 
    0x71, 0x7c, 0x7e, 0x94, 0x9d, 0xa5, 0xb4, 0xbc, 0xbe, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

C1Parser::Initializer C1Parser::_init;
