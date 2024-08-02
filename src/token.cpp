#include "token.h"

Token::Token() : m_type(TokenType::_ILLEGAL), m_value("ILLEGAL"){};

Token::Token(TokenType token) : m_type(token){};

Token::Token(TokenType token, const std::string &value)
    : m_type(token), m_value(value){};

bool Token::operator==(const Token &other) const {
  return m_type == other.m_type && m_value == other.m_value;
}
