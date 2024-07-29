#include "tokentype.h"

const std::string TokenTypeToString(TokenType type) {
  switch (type) {
    case _ILLEGAL: return "ILLEGAL";
    case _EOF: return "EOF";

    // Identifiers + Literals 
    case _IDENTIFIER: return "IDENTIFIER";
    case _INT_LITERAL: return "INT_LITERAL";

    // Operators
    case _ASSIGN: return "=";
    case _PLUS: return "+";
    case _MINUS: return "-";
    case _BANG: return "!";
    case _ASTERISK: return "*";
    case _SLASH: return "/";
    case _LT: return "<";
    case _GT: return ">";
    case _EQ: return "==";
    case _NEQ: return "!=";

    // Delimiters
    case _COMMA: return ",";
    case _SEMICOLON: return ";";
    case _LPAREN: return "(";
    case _RPAREN: return ")";
    case _LBRACE: return "{";
    case _RBRACE: return "}";

    // Keywords 
    case _FUNCTION: return "FUNCTION";
    case _LET: return "LET";
    case _TRUE: return "TRUE";
    case _FALSE: return "FALSE";
    case _IF: return "IF";
    case _ELSE: return "ELSE";
    case _RETURN: return "RETURN";

    default: return "UNKNOWN_TOKEN";
  }
}

