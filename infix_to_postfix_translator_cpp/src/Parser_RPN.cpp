#include "Parser_RPN.h"

#include "emit.hpp"
#include "error.hpp"

void Parser::parse(std::vector<Token> tokens) {
  _tokens = std::move(tokens);
  parse();
}

void Parser::parse() {
  _current = 0;
  _lookahead = _tokens[_current]; // the lexan provides tokens as the parser
                                  // asks for them
  while (_lookahead.token_type() != Token_Type::ezEOF) {
    expr();                       // begins syntax directed translation scheme
    match(Token_Type::SEMICOLON); // ensures that expressions end with ';'
  }
}

void Parser::expr() { // NOLINT
  Token old_look;
  term();
  while (true) {
    switch (_lookahead.token_type()) {
    case Token_Type::PLUS:
    case Token_Type::MINUS:
      old_look = _lookahead;
      match(_lookahead.token_type());
      term();
      emit(old_look.lexeme());
      continue;
    default:
      return;
    }
  }
}

void Parser::term() { // NOLINT
  Token old_look;
  factor();
  while (true) {
    switch (_lookahead.token_type()) {
    case Token_Type::STAR:
    case Token_Type::SLASH:
    case Token_Type::DIV:
    case Token_Type::MOD:
      old_look = _lookahead;
      match(_lookahead.token_type());
      factor();
      emit(old_look.lexeme());
      continue;
    default:
      return;
    }
  }
}

void Parser::factor() { // NOLINT
  switch (_lookahead.token_type()) {
  case Token_Type::LEFT_PAREN:
    match(Token_Type::LEFT_PAREN);
    expr();
    match(Token_Type::RIGHT_PAREN);
    break;
  case Token_Type::RIGHT_PAREN: // encounter a right paren before a left paren
  {
    if (_parentheses <= 0) {
      error("\nsyntax error: missing '(', unexpected ')'");
      throw std::runtime_error("\nsyntax error: missing '(', unexpected ')'");
    }
    if (_parentheses == 1) {
      error("\nsyntax error: empty parentheses \"()\"");
    }
  }
  case Token_Type::ID:
    emit(_lookahead.lexeme());
    match(Token_Type::ID);
    break;
  case Token_Type::NUM:
    emit(_lookahead.lexeme());
    match(Token_Type::NUM);
    break;
  default:
    error("\nsyntax error: unexpected", '"', _lookahead.lexeme(), '"');
  }
}

void Parser::match(Token_Type const tt) {
  if (_lookahead.token_type() == tt) {
    if (tt == Token_Type::SEMICOLON) { // print one expression per line
      std::cout << '\n';
    } else if (tt == Token_Type::LEFT_PAREN) {
      ++_parentheses;
    } else if (tt == Token_Type::RIGHT_PAREN) {
      --_parentheses;
    }
    _lookahead = _tokens[++_current];
  } else {
    if (tt == Token_Type::SEMICOLON) {
      error("\nsyntax error: missing ';' at end of statement");
    } else if (tt == Token_Type::RIGHT_PAREN) {
      error("\nsyntax error: missing ')'");
    } else {
      error("\nsyntax error: unexpected ", '"', _lookahead.lexeme(), '"');
    }
  }
}
