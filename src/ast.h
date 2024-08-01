#ifndef AST_H
#define AST_H

#include "token.h"
#include <string>
#include <vector>

class Node {
public:
  virtual std::string TokenLiteral() const = 0;
  virtual ~Node() = default;
};

class Statement : public Node {
public:
  virtual void statementNode() = 0;
  virtual ~Statement() = default;
};

class Expression : public Node {
public:
  virtual void expressionNode() = 0;
  virtual ~Expression() = default;
};

class Program : public Node {
public:
  std::string TokenLiteral() const override;
  std::vector<Statement *> m_statements;
};

class Identifier : public Expression {
public:
  void expressionNode() override;
  std::string TokenLiteral() const override;

  Token m_token; // TokenType::_IDENTIFIER token
  std::string m_value;
};

class LetStatement : public Statement {
public:
  void statementNode() override;
  std::string TokenLiteral() const override;

  Token m_token; // TokenType::_LET token
  Identifier *m_identifier_ptr;
  Expression *m_value_ptr;
};

#endif

