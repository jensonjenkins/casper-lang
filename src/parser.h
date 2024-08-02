#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "ast_base.h"
#include "token.h"
#include "tokenizer.h"
#include "tokentype.h"

typedef ast::Expression (*prefixParseFn)();
typedef ast::Expression (*infixParseFn)(ast::Expression);

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

  /**
   * @brief A mapping of how to parse a given token given its in the prefix
   * position (e.g. ++5, the ++ is prefix operator)
   */
  std::map<TokenType, prefixParseFn> prefixParseFns;

  /**
   * @brief A mapping of how to parse a given token given its in the infix
   * position (e.g. 5 + 3, the + is an infix operator)
   */
  std::map<TokenType, infixParseFn> infixParseFns;

  /**
   * @brief Collection of error messages during parsing
   */
  std::vector<std::string> errors;

  /**
   * @brief Advances the current and peek token cursors
   */
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

  void registerPrefix(const TokenType &t_type, prefixParseFn fn);
  void registerInfix(const TokenType &t_type, infixParseFn fn);

  bool curTokenIs(const TokenType &t_type);
  bool peekTokenIs(const TokenType &t_type);

  /**
   * @brief calls nextToken() if peekTokenIs returns true
   * @return boolean whether peekToken TokenType is equal to the expected
   * TokenType t_type;
   */
  bool expectPeek(const TokenType &t_type);
};

#endif
