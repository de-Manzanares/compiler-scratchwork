#ifndef INCLUDE_LEXER_H_
#define INCLUDE_LEXER_H_

#include "Lexer.h"
#include "Token.h"

#include <string>
#include <unordered_map>
#include <vector>

using value = uint64_t;

class Lexer {
 public:
  explicit Lexer(std::string str = "");
  std::vector<Token> lex_tokens();
  std::vector<Token> lex_tokens(std::string str);
  std::vector<Token> lex_tokens(std::vector<std::string> strings);

  static std::unordered_map<std::string, Token_Type> keywords;

 private:
  std::string _str;
  value _start{};             ///< first character of current lexeme
  value _current{};           ///< character currently being considered
  value _line = 1;            ///< current token line
  std::vector<Token> _tokens; ///< list of tokens

  void lex_token();
  [[nodiscard]] bool is_at_end() const;
  void push_token(Token_Type token, const std::string &content = "");
  void number();
  void keyword_or_id();
};

#endif // INCLUDE_LEXER_H_
