#ifndef AST_H
#define AST_H

#include "token.h"
#include <string>
#include <vector>

class Node {
public:
  virtual ~Node() = default;
  virtual std::string TokenLiteral() const = 0;
};

class Statement : public Node {
public:
  virtual void statementNode();
};

class Expression : public Node {
public:
  virtual void expressionNode();
};

class Program : public Node {
public:
  std::string TokenLiteral() const override;
private:
  std::vector<Statement> m_statements;
};

class Identifier : public Expression {
public:
  std::string TokenLiteral() const override;
private:
  Token m_token;
  std::string m_value;
};

class LetStatement : public Statement {
public:
  std::string TokenLiteral() const override;
private:
  Token m_token;
  Identifier* m_identifier_ptr;
  Expression* m_value_ptr;
};


#endif
