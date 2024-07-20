#include "Token.h"

#include <utility>

Token::Token(Token_Type const &token, std::string lexeme, std::string content,
             value const line)
    : _token_type(token), _lexeme(std::move(lexeme)),
      _content(std::move(content)), _line(line) {}

std::string Token::to_string() const {
  if (_token_type != Token_Type::ezEOF) {
    return _lexeme + " " + _content + " " + "line " + std::to_string(_line);
  }
  return "";
}
