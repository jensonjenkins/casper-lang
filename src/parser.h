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

  /**
   * @brief Parse 'let' statements
   *
   * Parse statements of the form 'let <identifier> = <expression>;'
   *
   * @return std::unique_ptr of the parsed let statement AST node
   */
  std::unique_ptr<ast::LetStatement> parseLetStatement();

  /**
   * @brief Parse 'return' statements
   *
   * Parse statements of the form 'return <expression>;'
   *
   * @return std::unique_ptr of the parsed return statement AST node
   */
  std::unique_ptr<ast::ReturnStatement> parseReturnStatement();

  bool curTokenIs(const TokenType &t_type);
  bool peekTokenIs(const TokenType &t_type);
  bool expectPeek(const TokenType &t_type);
};

#endif
