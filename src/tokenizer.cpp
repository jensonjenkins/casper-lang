#include "tokenizer.h"
#include "tokentype.h"

Tokenizer::Tokenizer(const std::string &src)
    : m_cursor(0), m_read_cursor(0), m_ch(0), m_src(src) {
  readChar();
};

Token Tokenizer::nextToken() {
  Token token;
  std::string m_str = std::string(1, m_ch);

  switch (m_ch) {
  case '=':
    token = Token(TokenType::_ASSIGN, m_str);
    break;
  case '+':
    token = Token(TokenType::_PLUS, m_str);
    break;
  case ';':
    token = Token(TokenType::_SEMICOLON, m_str);
    break;
  case '(':
    token = Token(TokenType::_LPAREN, m_str);
    break;
  case ')':
    token = Token(TokenType::_RPAREN, m_str);
    break;
  case '{':
    token = Token(TokenType::_LBRACE, m_str);
    break;
  case '}':
    token = Token(TokenType::_RBRACE, m_str);
    break;
  case ',':
    token = Token(TokenType::_COMMA, m_str);
    break;
  case 0:
    token = Token(TokenType::_EOF, "EOF");
    break;
  }
  readChar();
  return token;
}

void Tokenizer::readChar() {
  if (m_read_cursor >= m_src.size()) {
    m_ch = 0;
  } else {
    m_ch = m_src[m_read_cursor];
  }
  m_cursor = m_read_cursor;
  m_read_cursor++;
}
