#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "ast_base.h"
#include "token.h"
#include "tokenizer.h"
#include "tokentype.h"
#include <functional>

class Parser {
public:
  /**
   * @note std::function is used here to abstract away the underlying complexities
   * we need to deal with when dealing with member functions.
   */
  using prefixParseFn = std::function<std::shared_ptr<ast::Expression>()>;
  using infixParseFn = std::function<std::shared_ptr<ast::Expression>(ast::Expression)>;

  Parser(Tokenizer &t);

  ast::Program *parseProgram();

  const std::vector<std::string> Errors() const;
  void peekError(const TokenType &t_type);

  /**
   * @brief Enum showing order of parsing precedence for expressions
   */
  enum Precedence {
    _,
    LOWEST,
    EQUALS,
    LESSGREATER,
    SUM,
    PRODUCT,
    PREFIX,
    FCALL
  };

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

  /**
   * @brief Parse expression statements
   * @return std::unique_ptr of the parsed expression statement AST node
   */
  std::unique_ptr<ast::ExpressionStatement> parseExpressionStatement();

  /**
   * @brief Parse general expressions
   * @return std::unique_ptr of the parsed expression AST node
   */
  std::shared_ptr<ast::Expression>
  parseExpression(Parser::Precedence precedence);

  /**
   * @brief Parse expressions starting with an identifier
   * @return std::unique_ptr of the identifier AST node
   *
   * @note the only reason a static is used here is to conform to the
   * prefixParseFn typedef, i.e. the typedef expects no parameters and a member
   * function implicitly passes the class as an argument.
   */
  std::shared_ptr<ast::Expression> parseIdentifier();

  void registerPrefixFn(const TokenType &t_type, prefixParseFn fn);
  void registerInfixFn(const TokenType &t_type, infixParseFn fn);

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
