#include "parser_test.h"
#include "tokenizer_test.h"
#include <cstdlib>
#include <iostream>

int main() {
  std::cout << "running casper unit tests:\n" << std::endl;

  std::cout << "running RunTokenizerTests:" << std::endl;
  RunTokenizerTests();
  std::cout << std::endl;

  std::cout << "running RunParserTests:" << std::endl;
  RunParserTests();

  exit(EXIT_SUCCESS);
}
