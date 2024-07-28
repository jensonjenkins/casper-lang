#ifndef TOKEN_H
#define TOKEN_H

#include "tokentype.h"
#include <optional>
#include <string>

class Token {
public:
  Token(TokenType token, const std::string &value)
      : m_type(token), m_value(value){};
  Token(TokenType token) : m_type(token){};

  bool operator==(const Token &other) const {
    return m_type == other.m_type && m_value == other.m_value;
  }

private:
  TokenType m_type;
  std::optional<std::string> m_value;
};

#endif
