#include "../src/tokenizer.h"
#include <iostream>
#include <string>
#include <vector>

void TokenizerTest1() {
  std::string input = "=+(){};,";
  Tokenizer t(input);
  std::vector<Token> expected = {
      Token(TokenType::_ASSIGN, "="),    Token(TokenType::_PLUS, "+"),
      Token(TokenType::_LPAREN, "("),    Token(TokenType::_RPAREN, ")"),
      Token(TokenType::_LBRACE, "{"),    Token(TokenType::_RBRACE, "}"),
      Token(TokenType::_SEMICOLON, ";"), Token(TokenType::_COMMA, ",")};

  bool passed = true;

  for (Token expected_tok : expected) {
    Token tok = t.nextToken();
    if (tok.m_type != expected_tok.m_type) {
      passed = false;
      std::cout << "tokenizer_test[1] - tokentype wrong. ";
      std::cout << "expected='" << expected_tok.m_type << "', ";
      std::cout << "got='" << tok.m_type << "'" << std::endl;
    }
    if (tok.m_value != expected_tok.m_value) {
      passed = false;
      std::cout << "tokenizer_test[1] - tokenvalue wrong. ";
      std::cout << "expected='" << expected_tok.m_value << "', ";
      std::cout << "got='" << tok.m_value << "'" << std::endl;
    }
  }

  if (passed) {
    std::cout << "tokenizer_test[1] - passed." << std::endl;
  }
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

  Tokenizer t(input);
  std::vector<Token> expected = {
      Token(TokenType::_LET, "let"),
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
  };

  bool passed = true;

  for (Token expected_tok : expected) {
    Token tok = t.nextToken();
    if (tok.m_type != expected_tok.m_type) {
      passed = false;
      std::cout << "tokenizer_test[2] - tokentype wrong. ";
      std::cout << "expected='" << expected_tok.m_type << "', ";
      std::cout << "got='" << tok.m_type << "'" << std::endl;
    }
    if (tok.m_value != expected_tok.m_value) {
      passed = false;
      std::cout << "tokenizer_test[2] - tokenvalue wrong. ";
      std::cout << "expected='" << expected_tok.m_value << "', ";
      std::cout << "got='" << tok.m_value << "'" << std::endl;
    }
  }

  if (passed) {
    std::cout << "tokenizer_test[2] - passed." << std::endl;
  }
}

int main(int argc, char *argv[]) {

  // Tokenizer Tests
  TokenizerTest1();
  TokenizerTest2();

  return EXIT_SUCCESS;
}
