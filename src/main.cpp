#include "Lexer.h"
#include "Parser_RPN.h"

#include <fstream>
#include <iostream>
#include <string>

class Hatchling {
 public:
  static void run_file(std::string const &file_name);
  void run_repl();
  static void run(std::string const &str);

 private:
  bool error = false;
};

/**
 * Syntax-directed translation scheme
 *       start -> list myEOF
 *        list -> expr ; list | empty
 *        expr -> term moreterms
 *   moreterms -> + term { print('+') } moreterms
 *              | - term { print('-') } moreterms
 *              | empty
 *        term -> factor morefactors
 * morefactors -> * factor { print('*') } morefactors
 *              | / factor { print('/') } morefactors
 *              | div factor { print('DIV') } morefactors
 *              | mod factor { print('MOD') } morefactors
 *              | empty
 *      factor -> ( expr )
 *              | id { print(id.lexeme) }
 *              | num { print(num.value) }
 */

/**
 * @brief A simple one pass compiler:
 * translating infix expressions to reverse polish notation (postfix) form.
 * @details A syntax directed translator: uses a simple lexical analyzer
 * that feeds a top-down-recursive-descent-predictive parser, all the while
 * printing translations (or error messages) to stdout.
 * @return translation
 */
int main(const int argc, const char *argv[]) {
  if (argc > 2) {
    std::cout << "To convert a file : ./hatchling [file]\n";
    std::cout << "To enter REPL mode: ./hatchling \n";
  } else if (argc > 1) {
    Hatchling::run_file(argv[1]);
  } else {
    Hatchling hatchling;
    hatchling.run_repl();
  }
  return EXIT_SUCCESS;
}

void Hatchling::run_file(std::string const &file_name) {
  std::ifstream ifstream(file_name);
  try {
    if (!ifstream.is_open()) {
      throw std::runtime_error(file_name + " not found\n");
    }
  } catch ([[maybe_unused]] std::runtime_error &e) {
    std::cerr << "Failed to open file: " << e.what() << '\n';
  }
  std::vector<std::string> strings{};
  std::string str;
  while (std::getline(ifstream, str)) {
    strings.push_back(str);
  }
  Lexer lexer;
  Parser parser;
  parser.parse(lexer.lex_tokens(strings));
}

void Hatchling::run_repl() {
  std::string str;
  std::cout << "> ";
  while (std::getline(std::cin, str)) {
    run(str);
    std::cout << "\n> ";
    error = false;
  }
}

void Hatchling::run(std::string const &str) {
  Lexer lexer(str);
  Parser parser(lexer.lex_tokens());
  parser.parse();
}
