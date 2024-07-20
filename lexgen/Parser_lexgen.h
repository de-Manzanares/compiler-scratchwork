#ifndef INCLUDE_PARSER_RPN_H_
#define INCLUDE_PARSER_RPN_H_

#include "Token.h"
#include <utility>
#include <vector>

class Token;

class Parser {
 public:
  /// top-down-recursive-descent predictive parser
  explicit Parser(std::vector<Token> tokens = std::vector<Token>{})
      : _tokens(std::move(tokens)) {}
  void parse();
  void parse(std::vector<Token> tokens);

 private:
  value _current{}; ///< current token
  Token _lookahead; ///< predictive parser -- no backtracking
  std::vector<Token> _tokens;
  void expr();   ///< production in syntax directed translation scheme
  void term();   ///< production in syntax directed translation scheme
  void factor(); ///< production in syntax directed translation scheme
  void match(Token_Type tt);
};

#endif // INCLUDE_PARSER_RPN_H_
