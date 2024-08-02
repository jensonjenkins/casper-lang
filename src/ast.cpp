#include "ast.h"
#include "ast_base.h"
#include <memory>

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

std::string Program::toString() const {
  std::string buf;
  for (std::shared_ptr<Statement> stmt : m_statements) {
    buf += stmt->toString() + "\n";
  }
  return buf;
}

// Identifier Implementations
Identifier::Identifier(const Token token, const std::string value)
    : m_token(token), m_value(value){};

void Identifier::expressionNode() {};

std::string Identifier::TokenLiteral() const { return m_token.m_value; }

std::string Identifier::toString() const { return m_value; }

// LetStatement Implementations
LetStatement::LetStatement(const Token token,
                           std::unique_ptr<Identifier> identifier_ptr,
                           std::unique_ptr<Expression> expr_ptr)
    : m_token(token), m_identifier_ptr(std::move(identifier_ptr)),
      m_expr_ptr(std::move(expr_ptr)){};

void LetStatement::statementNode() {};

std::string LetStatement::TokenLiteral() const { return m_token.m_value; }

std::string LetStatement::toString() const {
  std::string buf;
  buf += this->TokenLiteral() + " " + m_identifier_ptr->m_value;
  buf += " = ";
  if (m_expr_ptr) { // TODO: remove nullptr check when expressions can be parsed
    buf += m_expr_ptr->toString();
  }
  buf += ";";
  return buf;
}

// ReturnStatement Implementations
ReturnStatement::ReturnStatement(const Token token,
                                 std::unique_ptr<Expression> return_value_ptr)
    : m_token(token), m_return_value_ptr(std::move(return_value_ptr)){};

void ReturnStatement::statementNode() {};

std::string ReturnStatement::TokenLiteral() const { return m_token.m_value; }

std::string ReturnStatement::toString() const {
  std::string buf;
  buf += this->TokenLiteral() + " ";
  buf += " = ";
  if (m_return_value_ptr) { // TODO: remove nullptr check when expressions can
                            // be parsed
    buf += m_return_value_ptr->toString();
  }
  buf += ";";
  return buf;
}

// ExpressionStatement Implementations
ExpressionStatement::ExpressionStatement(const Token token,
                                         std::unique_ptr<Expression> expr_ptr)
    : m_token(token), m_expr_ptr(std::move(expr_ptr)){};

void ExpressionStatement::statementNode() {};

std::string ExpressionStatement::TokenLiteral() const {
  return m_token.m_value;
}

std::string ExpressionStatement::toString() const {
  std::string buf;
  if (m_expr_ptr) { // TODO: remove nullptr check when expressions can be parsed
    buf += m_expr_ptr->toString();
  }
  buf += ";";
  return buf;
}

} // namespace ast
