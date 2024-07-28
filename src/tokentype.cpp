#include "tokentype.h"

const std::string TokenTypeToString(TokenType type) {
  switch (type) {
    case _ILLEGAL: return "ILLEGAL";
    case _EOF: return "EOF";
    case _IDENTIFIER: return "IDENTIFIER";
    case _INT_LITERAL: return "INT_LITERAL";
    case _ASSIGN: return "=";
    case _PLUS: return "+";
    case _COMMA: return ",";
    case _SEMICOLON: return ";";
    case _LPAREN: return "(";
    case _RPAREN: return ")";
    case _LBRACE: return "{";
    case _RBRACE: return "}";
    case _FUNCTION: return "FUNCTION";
    case _LET: return "LET";
    case _EXIT: return "EXIT";
    default: return "UNKNOWN_TOKEN";
  }
}

