#include "../src/tokenizer.h"
#include <iostream>
#include <string>
#include <vector>

void TokenizerTest1() {
  std::string input = "=+(){};,";
  Tokenizer tokenizer(input);
  std::vector<Token> tokens = tokenizer.tokenize();
  std::vector<Token> expected = {TokenType::_ASSIGN,    TokenType::_PLUS,
                                 TokenType::_LPAREN,    TokenType::_RPAREN,
                                 TokenType::_LBRACE,    TokenType::_RBRACE,
                                 TokenType::_SEMICOLON, TokenType::_COMMA};

  if (tokens == expected) {
    std::cout << "Tokenizer Test 1: Passed" << std::endl;
  } else {
    std::cout << "Tokenizer Test 1: Failed" << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::cout << "Running Casper Tests: " << std::endl;

  // Tokenizer Tests
  TokenizerTest1();

  return EXIT_SUCCESS;
}
