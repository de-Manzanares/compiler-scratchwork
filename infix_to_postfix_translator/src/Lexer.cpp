#include "Lexer.h"

#include "error.hpp"

#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

Lexer::Lexer(std::string str) : _str(std::move(str)) {}

std::unordered_map<std::string, Token_Type> Lexer::keywords = {
    {"div", Token_Type::DIV}, {"mod", Token_Type::MOD}};

std::vector<Token> Lexer::lex_tokens(std::vector<std::string> strings) {
  std::vector<std::vector<Token>> tmp;
  for (auto const &str : strings) {
    tmp.push_back(lex_tokens(str));
    // the way it is set up now, at the end of each string an ezEOF token is
    // added to the token list. Fine, however, that wont' work if we are trying
    // to parse more than one string. So, ... pop_back() :-)
    // not the best solution, but it'll work for now
    if (str != strings.back()) {
      tmp.back().pop_back();
    }
  }
  _tokens.clear();
  for (auto const &v : tmp) {
    for (auto const &t : v) {
      _tokens.push_back(t);
    }
  }
  return _tokens;
}

std::vector<Token> Lexer::lex_tokens(std::string str) {
  _start = _current = 0;
  _str = std::move(str);
  _tokens.clear();
  return lex_tokens();
}

std::vector<Token> Lexer::lex_tokens() {
  while (!is_at_end()) {
    _start = _current; // move to start of next lexeme
    lex_token();
  }
  // final EOF token
  _tokens.emplace_back(Token_Type::ezEOF, "", "", _line);
  return _tokens;
}

void Lexer::lex_token() {
  using tt = Token_Type;
  switch (unsigned char const ch = _str[_current++]) {
  case ' ': // ignore whitespaces
  case '\r':
  case '\t': break;
  case '\n': // count line
    _line++;
    break;
  case '(': // single character tokens
    push_token(tt::LEFT_PAREN);
    break;
  case ')': push_token(tt::RIGHT_PAREN); break;
  case '+': push_token(tt::PLUS); break;
  case '-': push_token(tt::MINUS); break;
  case '*': push_token(tt::STAR); break;
  case '/': push_token(tt::SLASH); break;
  case ';': push_token(tt::SEMICOLON); break;

  default: {
    if (std::isdigit(ch)) { // we only deal with single digits
      number();
    } else if (std::isalpha(ch)) {
      keyword_or_id(); //
    } else {
      error("unknowwn token: ", ch);
    }
  }
  }
}

bool Lexer::is_at_end() const { return _current >= _str.length(); }

void Lexer::push_token(Token_Type token, std::string const &content) {
  _tokens.emplace_back(token, _str.substr(_start, _current - _start), content,
                       _line);
}
void Lexer::number() {
  while (std::isdigit(_str[_current])) {
    ++_current; // read to the end of the number
  }
  push_token(Token_Type::NUM);
}

void Lexer::keyword_or_id() {
  while (std::isalnum(_str[_current])) {
    ++_current; // read to the end of word
  }
  if (const std::string lexeme = _str.substr(_start, _current - _start);
      // !keywords.contains(lexeme)) {
      std::find_if(keywords.begin(), keywords.end(), [=](const auto x) {
        return x.first == lexeme;
      }) != keywords.end()) {
    push_token(Token_Type::ID);
  } else {
    push_token(keywords[lexeme]);
  }
}
