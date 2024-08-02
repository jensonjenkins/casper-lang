#ifndef AST_BASE_H
#define AST_BASE_H

#include "token.h"
#include <memory>
#include <string>
#include <vector>

namespace ast {

class Node {
public:
  virtual std::string TokenLiteral() const = 0;
  virtual ~Node() = default;
  virtual std::string toString() const = 0;
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

} // namespace ast

#endif
