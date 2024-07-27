#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <optional>
#include "tokentype.h"

struct Token{
    TokenType m_token;
    std::optional<std::string> m_value;
    Token(TokenType token, const std::string& value): m_token(token), m_value(value){};
    Token(TokenType token): m_token(token){};
};

#endif
