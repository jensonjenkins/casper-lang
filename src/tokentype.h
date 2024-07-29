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
    _MINUS,
    _BANG, 
    _ASTERISK,
    _SLASH,

    _LT,
    _GT,
    _NEQ,
    _EQ,

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
    _TRUE,
    _FALSE,
    _IF,
    _ELSE,
    _RETURN
};

const std::string TokenTypeToString(TokenType type);

#endif

