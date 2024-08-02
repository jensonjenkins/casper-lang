#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "token.h"
#include "tokenizer.h"
#include "tokentype.h"

class Parser {
public:
  Parser(Tokenizer &t);

  ast::Program *parseProgram();

  const std::vector<std::string> Errors() const;
  void peekError(const TokenType &t_type);

private:
  Tokenizer m_t;

  Token m_cur_token;
  Token m_peek_token;

  std::vector<std::string> errors;

  void nextToken();

  std::unique_ptr<ast::Statement> parseStatement();
  std::unique_ptr<ast::LetStatement> parseLetStatement();

  bool curTokenIs(const TokenType &t_type);
  bool peekTokenIs(const TokenType &t_type);
  bool expectPeek(const TokenType &t_type);
};

#endif
