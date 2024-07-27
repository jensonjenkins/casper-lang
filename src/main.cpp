#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include "tokenizer.h"

enum class TokenType { exit, int_lit, semi_colon };

struct Token {
  TokenType type;
  std::optional<std::string> value;
  Token(TokenType type, std::optional<std::string> value)
      : type(type), value(value){};
  Token(TokenType type) : Token(type, ""){};
};


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
