#ifndef AST_H
#define AST_H

#include "ast_base.h"
#include <memory>

namespace ast {

class Program : public Node {
public:
  Program();

  std::string TokenLiteral() const override;
  std::string toString() const override;
  std::vector<std::shared_ptr<Statement>> m_statements;
};

class Identifier : public Expression {
public:
  Identifier(const Token token, const std::string value);

  void expressionNode() override;
  std::string toString() const override;
  std::string TokenLiteral() const override;

  Token m_token; // TokenType::_IDENTIFIER token
  std::string m_value;
};

class LetStatement : public Statement {
public:
  LetStatement() = default;
  LetStatement(const Token token, std::unique_ptr<Identifier> identifier_ptr,
               std::unique_ptr<Expression> value_ptr);

  void statementNode() override;
  std::string toString() const override;
  std::string TokenLiteral() const override;

  Token m_token; // TokenType::_LET token
  std::unique_ptr<Identifier> m_identifier_ptr;
  std::unique_ptr<Expression> m_expr_ptr;
};

class ReturnStatement : public Statement {
public:
  ReturnStatement() = default;
  ReturnStatement(const Token token, std::unique_ptr<Expression> return_value_ptr);

  void statementNode() override;
  std::string toString() const override;
  std::string TokenLiteral() const override;

  Token m_token; // TokenType::_RETURN token
  std::unique_ptr<Expression> m_return_value_ptr;
};

class ExpressionStatement : public Statement {
public:
  ExpressionStatement() = default;
  ExpressionStatement(const Token token, std::shared_ptr<Expression> expr_ptr);

  void statementNode() override;
  std::string toString() const override;
  std::string TokenLiteral() const override;

  Token m_token; // first token in the expression
  std::shared_ptr<Expression> m_expr_ptr;
};

} // namespace ast

#endif
