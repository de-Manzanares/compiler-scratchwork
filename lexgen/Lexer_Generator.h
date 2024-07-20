#ifndef LEXER_GENERATOR_HPP
#define LEXER_GENERATOR_HPP
#include <string>

class Lexer_Generator {
 public:
  void write() const;
  std::string &infile() { return _infile; }
  std::string &outdir() { return _outdir; }

 private:
  std::string _infile;
  std::string _outdir;
};

#endif // LEXER_GENERATOR_HPP
