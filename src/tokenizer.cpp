#include "tokenizer.h"
#include "tokentype.h"
#include <cctype>

Tokenizer::Tokenizer(const std::string &src)
    : m_cursor(0), m_read_cursor(0), m_ch(0), m_src(src) {
  readChar();
};

void Tokenizer::readChar() {
  if (m_read_cursor >= m_src.size()) {
    m_ch = 0;
  } else {
    m_ch = m_src[m_read_cursor];
  }
  m_cursor = m_read_cursor;
  m_read_cursor++;
}

char Tokenizer::peekChar() {
  if (m_read_cursor >= m_src.size()) {
    return 0;
  } else {
    return m_src[m_read_cursor];
  }
}

std::string Tokenizer::readDigits() {
  std::string token_str = "";
  while (std::isdigit(m_ch)) {
    token_str += m_ch;
    readChar();
  }
  return token_str;
}

std::string Tokenizer::readIdentifier() {
  std::string token_str = "";
  while (std::isalpha(m_ch) || m_ch == '_') {
    token_str += m_ch;
    readChar();
  }
  return token_str;
}

TokenType Tokenizer::lookupIdentifier(std::string input) {
  std::map<std::string, TokenType>::const_iterator it = keywords.find(input);
  if (it == keywords.end()) {
    return TokenType::_IDENTIFIER;
  } else {
    return it->second;
  }
}

void Tokenizer::consumeWhitespace() {
  while (std::isspace(m_ch)) {
    readChar();
  }
}

void Tokenizer::consumeSingleToken(Token &token, const Token &token_object) {
  token = token_object;
  readChar();
};

Token Tokenizer::nextToken() {
  Token token;
  consumeWhitespace();

  std::string m_str = std::string(1, m_ch);

  switch (m_ch) {
  case '=':
    if (peekChar() == '=') {
      readChar();
      std::string c_str = std::string(1, m_ch);
      consumeSingleToken(token, Token(TokenType::_EQ, m_str + c_str));
    } else {
      consumeSingleToken(token, Token(TokenType::_ASSIGN, m_str));
    }
    break;
  case '+':
    consumeSingleToken(token, Token(TokenType::_PLUS, m_str));
    break;
  case '-':
    consumeSingleToken(token, Token(TokenType::_MINUS, m_str));
    break;
  case '!':
    if (peekChar() == '=') {
      readChar();
      std::string c_str = std::string(1, m_ch);
      consumeSingleToken(token, Token(TokenType::_NEQ, m_str + c_str));
    } else {
      consumeSingleToken(token, Token(TokenType::_BANG, m_str));
    }
    break;
  case '*':
    consumeSingleToken(token, Token(TokenType::_ASTERISK, m_str));
    break;
  case '/':
    consumeSingleToken(token, Token(TokenType::_SLASH, m_str));
    break;
  case '<':
    consumeSingleToken(token, Token(TokenType::_LT, m_str));
    break;
  case '>':
    consumeSingleToken(token, Token(TokenType::_GT, m_str));
    break;
  case ';':
    consumeSingleToken(token, Token(TokenType::_SEMICOLON, m_str));
    break;
  case '(':
    consumeSingleToken(token, Token(TokenType::_LPAREN, m_str));
    break;
  case ')':
    consumeSingleToken(token, Token(TokenType::_RPAREN, m_str));
    break;
  case '{':
    consumeSingleToken(token, Token(TokenType::_LBRACE, m_str));
    break;
  case '}':
    consumeSingleToken(token, Token(TokenType::_RBRACE, m_str));
    break;
  case ',':
    consumeSingleToken(token, Token(TokenType::_COMMA, m_str));
    break;
  case 0:
    consumeSingleToken(token, Token(TokenType::_EOF, ""));
    break;
  default:
    if (std::isalpha(m_ch) || m_ch == '_') {
      std::string token_str = readIdentifier();
      TokenType tokentype = lookupIdentifier(token_str);
      token = Token(tokentype, token_str);
    } else if (std::isdigit(m_ch)) {
      std::string token_str = readDigits();
      token = Token(TokenType::_INT_LITERAL, token_str);
    } else {
      token = Token(TokenType::_ILLEGAL, m_str);
    }
    break;
  }

  return token;
}

