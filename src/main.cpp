#include "tokenizer.h"
#include "tokentype.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Incorrect usage!" << std::endl;
    std::cerr << "Syntax: csp <file_name>.boo" << std::endl;
    return EXIT_FAILURE;
  }

  // Read input file as string stream
  std::string file_content;
  {
    std::stringstream file_stream;
    std::ifstream input_file(argv[1]);
    file_stream << input_file.rdbuf();
    file_content = file_stream.str();
  }

  return EXIT_SUCCESS;
}

