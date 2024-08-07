#include "parser.h"
#include "ast.h"
#include "ast_base.h"
#include "tokentype.h"
#include <memory>

Parser::Parser(Tokenizer &t) : m_t(t) {
  this->nextToken();
  this->nextToken();

  registerPrefixFn(TokenType::_IDENTIFIER,
                   std::bind(&Parser::parseIdentifier, this));
};

void Parser::nextToken() {
  m_cur_token = m_peek_token;
  m_peek_token = m_t.nextToken();
}

const std::vector<std::string> Parser::Errors() const { return this->errors; }

void Parser::peekError(const TokenType &t_type) {
  std::string error_msg = "Expected next token to be \"" +
                          TokenTypeToString(t_type) + "\", got \"" +
                          TokenTypeToString(m_peek_token.m_type) + "\"";
  errors.push_back(error_msg);
}

ast::Program *Parser::parseProgram() {
  // TODO: Make sure to care for memory leaks, maybe use std::unique_ptr?
  ast::Program *program = new ast::Program();

  while (m_cur_token.m_type != TokenType::_EOF) {
    std::unique_ptr<ast::Statement> stmt = parseStatement();
    if (stmt) {
      program->m_statements.push_back(std::move(stmt));
    }
    nextToken();
  }

  return program;
}

std::unique_ptr<ast::Statement> Parser::parseStatement() {
  switch (m_cur_token.m_type) {
  case TokenType::_LET:
    return parseLetStatement();
    break;
  case TokenType::_RETURN:
    return parseReturnStatement();
    break;
  default:
    return parseExpressionStatement();
  }
}

bool Parser::curTokenIs(const TokenType &t_type) {
  return m_cur_token.m_type == t_type;
}

bool Parser::peekTokenIs(const TokenType &t_type) {
  return m_peek_token.m_type == t_type;
}

bool Parser::expectPeek(const TokenType &t_type) {
  if (peekTokenIs(t_type)) {
    nextToken();
    return true;
  }
  peekError(t_type);
  return false;
}

std::unique_ptr<ast::LetStatement> Parser::parseLetStatement() {
  Token let_token = m_cur_token;

  if (!expectPeek(TokenType::_IDENTIFIER)) {
    return nullptr;
  }

  std::unique_ptr<ast::Identifier> identifier_ptr =
      std::make_unique<ast::Identifier>(m_cur_token, m_cur_token.m_value);

  if (!expectPeek(TokenType::_ASSIGN)) {
    return nullptr;
  }

  // TODO: Temporarily, we skip expressions until we find a
  // semicolon just to pass unit tests.
  while (!curTokenIs(TokenType::_SEMICOLON)) {
    nextToken();
  }

  // TODO: Temporarily, we set Expression value_ptr to nullptr.
  return std::make_unique<ast::LetStatement>(
      let_token, std::move(identifier_ptr), nullptr);
}

std::unique_ptr<ast::ReturnStatement> Parser::parseReturnStatement() {
  Token ret_token = m_cur_token;

  // TODO: Temporarily, we skip expressions until we find a
  // semicolon just to pass unit tests.
  while (!curTokenIs(TokenType::_SEMICOLON)) {
    nextToken();
  }

  // TODO: Temporarily, we set return_value to nullptr.
  return std::make_unique<ast::ReturnStatement>(ret_token, nullptr);
}

std::unique_ptr<ast::ExpressionStatement> Parser::parseExpressionStatement() {
  Token cur_token = m_cur_token;
  std::shared_ptr<ast::Expression> expr = parseExpression(Precedence::LOWEST);

  std::unique_ptr<ast::ExpressionStatement> expr_stmt =
      std::make_unique<ast::ExpressionStatement>(m_cur_token, expr);

  if (peekTokenIs(TokenType::_SEMICOLON)) {
    nextToken();
  }
  return expr_stmt;
}

std::shared_ptr<ast::Expression>
Parser::parseExpression(Parser::Precedence precedence) {
  std::map<TokenType, prefixParseFn>::iterator it =
      prefixParseFns.find(m_cur_token.m_type);

  if (it == prefixParseFns.end()) {
    return nullptr;
  }
  std::shared_ptr<ast::Expression> left_expr = it->second();

  return left_expr;
}

std::shared_ptr<ast::Expression> Parser::parseIdentifier() {
  std::shared_ptr<ast::Identifier> ident =
      std::make_shared<ast::Identifier>(m_cur_token, m_cur_token.m_value);
  return ident;
}

void Parser::registerPrefixFn(const TokenType &t_type, prefixParseFn fn) {
  prefixParseFns[t_type] = fn;
};

void Parser::registerInfixFn(const TokenType &t_type, infixParseFn fn) {
  infixParseFns[t_type] = fn;
};
