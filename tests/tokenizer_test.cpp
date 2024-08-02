#include "tokenizer_test.h"
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
      std::cout << "expected=\"" << expected_tok.m_type << "\", ";
      std::cout << "got=\"" << tok.m_type << "\"" << std::endl;
      exit(EXIT_FAILURE);
    }
    if (tok.m_value != expected_tok.m_value) {
      passed = false;
      std::cout << "tokenizer_test[" << tc << "] - tokenvalue wrong. ";
      std::cout << "expected=\"" << expected_tok.m_value << "\", ";
      std::cout << "got=\"" << tok.m_value << "\"" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  if (passed) {
    std::cout << "ok\t" << "tokenizer_test[" << tc << "]" << std::endl;
  }
}

// ====================================================================================
//                                       Testcases
// ====================================================================================

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

void TokenizerTest3() {
  std::string input = R"(
  !-/*5;
  5 < 10 > 5;
  )";

  std::vector<Token> expected = {Token(TokenType::_BANG, "!"),
                                 Token(TokenType::_MINUS, "-"),
                                 Token(TokenType::_SLASH, "/"),
                                 Token(TokenType::_ASTERISK, "*"),
                                 Token(TokenType::_INT_LITERAL, "5"),
                                 Token(TokenType::_SEMICOLON, ";"),

                                 Token(TokenType::_INT_LITERAL, "5"),
                                 Token(TokenType::_LT, "<"),
                                 Token(TokenType::_INT_LITERAL, "10"),
                                 Token(TokenType::_GT, ">"),
                                 Token(TokenType::_INT_LITERAL, "5"),
                                 Token(TokenType::_SEMICOLON, ";"),
                                 Token(TokenType::_EOF, "")};

  TestTokenizer(input, expected, 3);
}

void TokenizerTest4() {
  std::string input = R"(
  if(5 < 10) {
    return true;
  } else {
    return false;
  }

  10 == 10;
  10 != 9;
  )";

  std::vector<Token> expected = {
      Token(TokenType::_IF, "if"),          Token(TokenType::_LPAREN, "("),
      Token(TokenType::_INT_LITERAL, "5"),  Token(TokenType::_LT, "<"),
      Token(TokenType::_INT_LITERAL, "10"), Token(TokenType::_RPAREN, ")"),
      Token(TokenType::_LBRACE, "{"),       Token(TokenType::_RETURN, "return"),
      Token(TokenType::_TRUE, "true"),      Token(TokenType::_SEMICOLON, ";"),
      Token(TokenType::_RBRACE, "}"),       Token(TokenType::_ELSE, "else"),
      Token(TokenType::_LBRACE, "{"),       Token(TokenType::_RETURN, "return"),
      Token(TokenType::_FALSE, "false"),    Token(TokenType::_SEMICOLON, ";"),
      Token(TokenType::_RBRACE, "}"),

      Token(TokenType::_INT_LITERAL, "10"), Token(TokenType::_EQ, "=="),
      Token(TokenType::_INT_LITERAL, "10"), Token(TokenType::_SEMICOLON, ";"),

      Token(TokenType::_INT_LITERAL, "10"), Token(TokenType::_NEQ, "!="),
      Token(TokenType::_INT_LITERAL, "9"),  Token(TokenType::_SEMICOLON, ";"),
  };

  TestTokenizer(input, expected, 4);
}

void RunTokenizerTests() {
  TokenizerTest1();
  TokenizerTest2();
  TokenizerTest3();
  TokenizerTest4();
  std::cout << "passed\t(4/4)" << std::endl;
}
