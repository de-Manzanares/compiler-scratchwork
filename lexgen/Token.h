#ifndef INCLUDE_TOKEN_H_
#define INCLUDE_TOKEN_H_
#include <string>

using value = uint64_t;

enum class Token_Type {
  NILL,



  ezEOF
};

class Token {
 public:
  explicit Token(Token_Type const &token = Token_Type::NILL,
                 std::string lexeme = "", std::string content = "",
                 value line = 1);
  [[nodiscard]] std::string to_string() const;
  [[nodiscard]] Token_Type const &token_type() const { return _token_type; }
  [[nodiscard]] std::string const &lexeme() const { return _lexeme; }
  [[nodiscard]] value const &line() const { return _line; }

 private:
  Token_Type _token_type;
  std::string _lexeme;
  std::string _content;
  value _line;
};

#endif // INCLUDE_TOKEN_H_
