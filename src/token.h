#ifndef TOKEN_H
#define TOKEN_H

#include "tokentype.h"
#include <string>

struct Token {
  Token() : m_type(TokenType::_ILLEGAL), m_value("ILLEGAL"){};

  Token(TokenType token, const std::string &value)
      : m_type(token), m_value(value){};

  Token(TokenType token) : m_type(token){};

  bool operator==(const Token &other) const {
    return m_type == other.m_type && m_value == other.m_value;
  }

  TokenType m_type;

  std::string m_value;
};

#endif
