#include "parser.h"

Parser::Parser(Tokenizer &t): m_t(t){
    this->nextToken(); 
    this->nextToken(); 
};

void Parser::nextToken(){
    m_cur_token = m_peek_token; 
    m_peek_token = m_t.nextToken();
}

Program* Parser::parseProgram(){
    return nullptr;
}


