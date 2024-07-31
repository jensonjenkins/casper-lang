#include "ast.h"

std::string Program::TokenLiteral() const {
    if(m_statements.size() > 0){
        return m_statements[0].TokenLiteral();
    }else{
        return "";
    }
}

std::string Identifier::TokenLiteral() const{
    return m_token.m_value;
}

std::string LetStatement::TokenLiteral() const{
    return m_token.m_value;
}



