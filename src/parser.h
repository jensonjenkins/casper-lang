#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "tokenizer.h"
#include "token.h"

class Parser{
public:
    Parser(Tokenizer &t);

    void nextToken();

    Program* parseProgram();

private:
    Tokenizer m_t;

    Token m_cur_token;
    Token m_peek_token;
};



#endif
