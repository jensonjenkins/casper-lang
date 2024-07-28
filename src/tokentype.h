#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include <string>

enum TokenType{
    _ILLEGAL,
    _EOF,

    // Identifiers + Literals
    _IDENTIFIER,
    _INT_LITERAL,

    // Operators
    _ASSIGN,
    _PLUS,

    // Delimiters
    _COMMA,
    _SEMICOLON,

    _LPAREN,
    _RPAREN,
    _LBRACE,
    _RBRACE,
    
    // Keywords
    _FUNCTION,
    _LET,
    _EXIT
};

const std::string TokenTypeToString(TokenType type);

#endif
