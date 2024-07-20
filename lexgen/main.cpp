#include "Lexer_Generator.h"
#include <filesystem>
#include <fstream>
#include <iostream>

void check_arguments(int const argc, char const *argv[]);

//***************** BEGIN MAIN ***********************************************//

int main(int const argc, char const *argv[]) {
  check_arguments(argc, argv); // check arguments, if all is good, keep goin!
  Lexer_Generator lg;
  lg.infile() = argv[1]; // set paths
  lg.outdir() = argv[2];
  lg.write();

  return EXIT_SUCCESS;
}
//***************** END MAIN *************************************************//

void check_arguments(int const argc, char const *argv[]) {
  try {
    if (argc != 3) {
      throw std::runtime_error(
          "Usage: ./lexgen <inputfile> <output directory>");
    }
    std::string const infile = argv[1];
    std::string const outdir = argv[2];
    if (!std::filesystem::exists(argv[1])) {
      throw std::runtime_error("Cannot open file: \"" + infile +
                               "\" not found");
    }
    if (!std::filesystem::is_directory(outdir)) {
      throw std::runtime_error("Cannot write to directory: \"" + outdir +
                               "\" not found");
    }
  } catch (std::runtime_error &e) {
    std::cerr << e.what();
    exit(1);
  }
}