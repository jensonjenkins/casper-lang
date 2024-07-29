#include "../src/tokenizer.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

void TestTokenizer(std::string input, const std::vector<Token> expected,
                   int tc) {
  Tokenizer t(input);
  bool passed = true;

  for (Token expected_tok : expected) {
    Token tok = t.nextToken();
    if (tok.m_type != expected_tok.m_type) {
      passed = false;
      std::cout << "tokenizer_test[" << tc << "] - tokentype wrong. ";
      std::cout << "expected=" << expected_tok.m_type << ", ";
      std::cout << "got=" << tok.m_type << "" << std::endl;
      exit(EXIT_FAILURE);
    }
    if (tok.m_value != expected_tok.m_value) {
      passed = false;
      std::cout << "tokenizer_test[" << tc << "] - tokenvalue wrong. ";
      std::cout << "expected=" << expected_tok.m_value << ", ";
      std::cout << "got=" << tok.m_value << "" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  if (passed) {
    std::cout << "tokenizer_test[" << tc << "] - passed." << std::endl;
  }
}

void TokenizerTest1() {
  std::string input = "=+(){};,";
  std::vector<Token> expected = {
      Token(TokenType::_ASSIGN, "="),    Token(TokenType::_PLUS, "+"),
      Token(TokenType::_LPAREN, "("),    Token(TokenType::_RPAREN, ")"),
      Token(TokenType::_LBRACE, "{"),    Token(TokenType::_RBRACE, "}"),
      Token(TokenType::_SEMICOLON, ";"), Token(TokenType::_COMMA, ","),
      Token(TokenType::_EOF, "")};

  TestTokenizer(input, expected, 1);
}

void TokenizerTest2() {
  std::string input = R"(
  let five = 5;
  let ten = 10;

  let add = fn(x, y){
    x + y;
  };

  let result = add(five, ten);
  )";

  std::vector<Token> expected = {Token(TokenType::_LET, "let"),
                                 Token(TokenType::_IDENTIFIER, "five"),
                                 Token(TokenType::_ASSIGN, "="),
                                 Token(TokenType::_INT_LITERAL, "5"),
                                 Token(TokenType::_SEMICOLON, ";"),

                                 Token(TokenType::_LET, "let"),
                                 Token(TokenType::_IDENTIFIER, "ten"),
                                 Token(TokenType::_ASSIGN, "="),
                                 Token(TokenType::_INT_LITERAL, "10"),
                                 Token(TokenType::_SEMICOLON, ";"),

                                 Token(TokenType::_LET, "let"),
                                 Token(TokenType::_IDENTIFIER, "add"),
                                 Token(TokenType::_ASSIGN, "="),
                                 Token(TokenType::_FUNCTION, "fn"),
                                 Token(TokenType::_LPAREN, "("),
                                 Token(TokenType::_IDENTIFIER, "x"),
                                 Token(TokenType::_COMMA, ","),
                                 Token(TokenType::_IDENTIFIER, "y"),
                                 Token(TokenType::_RPAREN, ")"),
                                 Token(TokenType::_LBRACE, "{"),
                                 Token(TokenType::_IDENTIFIER, "x"),
                                 Token(TokenType::_PLUS, "+"),
                                 Token(TokenType::_IDENTIFIER, "y"),
                                 Token(TokenType::_SEMICOLON, ";"),
                                 Token(TokenType::_RBRACE, "}"),
                                 Token(TokenType::_SEMICOLON, ";"),

                                 Token(TokenType::_LET, "let"),
                                 Token(TokenType::_IDENTIFIER, "result"),
                                 Token(TokenType::_ASSIGN, "="),
                                 Token(TokenType::_IDENTIFIER, "add"),
                                 Token(TokenType::_LPAREN, "("),
                                 Token(TokenType::_IDENTIFIER, "five"),
                                 Token(TokenType::_COMMA, ","),
                                 Token(TokenType::_IDENTIFIER, "ten"),
                                 Token(TokenType::_RPAREN, ")"),
                                 Token(TokenType::_SEMICOLON, ";"),

                                 Token(TokenType::_EOF, "")};

  TestTokenizer(input, expected, 2);
}

int main(int argc, char *argv[]) {

  // Tokenizer Tests
  TokenizerTest1();
  TokenizerTest2();

  return EXIT_SUCCESS;
}
