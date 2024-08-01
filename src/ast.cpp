#include "ast.h"
#include <iostream>

// ast::Program Implementations
ast::Program::Program()
    : m_statements(std::vector<std::shared_ptr<ast::Statement>>(0)) {
};

std::string ast::Program::TokenLiteral() const {
  if (m_statements.size() > 0) {
    return m_statements[0]->TokenLiteral();
  } else {
    return "";
  }
}

// ast::Identifier Implementations
ast::Identifier::Identifier(const Token token, const std::string value)
    : m_token(token), m_value(value){};

void ast::Identifier::expressionNode() {};

std::string ast::Identifier::TokenLiteral() const { return m_token.m_value; }

// ast::LetStatement Implementations
ast::LetStatement::LetStatement(const Token token,
                                std::shared_ptr<ast::Identifier> identifier_ptr,
                                Expression *value_ptr)
    : m_token(token), m_identifier_ptr(identifier_ptr),
      m_value_ptr(value_ptr){};

void ast::LetStatement::statementNode() {};

std::string ast::LetStatement::TokenLiteral() const { return m_token.m_value; }
