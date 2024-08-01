#ifndef AST_H
#define AST_H

#include "ast_base.h"
#include <memory>

namespace ast {

class Program : public Node {
public:
  Program();

  std::string TokenLiteral() const override;
  std::vector<std::shared_ptr<Statement>> m_statements;
};

class Identifier : public Expression {
public:
  Identifier(const Token token, const std::string value);

  void expressionNode() override;
  std::string TokenLiteral() const override;

  Token m_token; // TokenType::_IDENTIFIER token
  std::string m_value;
};

class LetStatement : public Statement {
public:
  LetStatement() = default;
  LetStatement(const Token token, std::shared_ptr<Identifier> identifier_ptr,
               Expression *value_ptr);

  void statementNode() override;
  std::string TokenLiteral() const override;

  Token m_token; // TokenType::_LET token
  std::shared_ptr<Identifier> m_identifier_ptr;
  Expression *m_value_ptr;
};

} // namespace ast

#endif
