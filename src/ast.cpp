#include "ast.h"
#include "ast_base.h"

namespace ast {

// Program Implementations
Program::Program(){};

std::string Program::TokenLiteral() const {
  if (m_statements.size() > 0) {
    return m_statements[0]->TokenLiteral();
  } else {
    return "";
  }
}

// Identifier Implementations
Identifier::Identifier(const Token token, const std::string value)
    : m_token(token), m_value(value){};

void Identifier::expressionNode() {};

std::string Identifier::TokenLiteral() const { return m_token.m_value; }

// LetStatement Implementations
LetStatement::LetStatement(const Token token,
                           std::shared_ptr<Identifier> identifier_ptr,
                           std::unique_ptr<Expression> value_ptr)
    : m_token(token), m_identifier_ptr(identifier_ptr),
      m_value_ptr(std::move(value_ptr)){};

void LetStatement::statementNode() {};

std::string LetStatement::TokenLiteral() const { return m_token.m_value; }

// ReturnStatement Implementations
ReturnStatement::ReturnStatement(const Token token,
                                 std::unique_ptr<Expression> value_ptr)
    : m_token(token), m_value_ptr(std::move(value_ptr)){};

void ReturnStatement::statementNode() {};

std::string ReturnStatement::TokenLiteral() const { return m_token.m_value; }

} // namespace ast
