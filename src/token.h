#ifndef TOKEN_H
#define TOKEN_H

#include "tokentype.h"
#include <string>

struct Token {
  Token();

  Token(TokenType token, const std::string &value);

  Token(TokenType token);

  bool operator==(const Token &other) const;

  TokenType m_type;

  std::string m_value;
};

#endif
