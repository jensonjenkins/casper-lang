#include "parser.h"
#include "ast.h"
#include <iostream>
#include <memory>

Parser::Parser(Tokenizer &t) : m_t(t) {
  this->nextToken();
  this->nextToken();
};

void Parser::nextToken() {
  m_cur_token = m_peek_token;
  m_peek_token = m_t.nextToken();
}

ast::Program *Parser::parseProgram() {
  // TODO: Make sure to care for memory leaks, maybe use std::unique_ptr?
  ast::Program *program = new ast::Program();

  while (m_cur_token.m_type != TokenType::_EOF) {
    std::shared_ptr<ast::Statement> stmt = parseStatement();
    if (stmt) {
      program->m_statements.push_back(stmt);
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
  default:
    return nullptr;
  }
}

bool Parser::curTokenIs(const TokenType &type) {
  return m_cur_token.m_type == type;
}

bool Parser::peekTokenIs(const TokenType &type) {
  return m_peek_token.m_type == type;
}

bool Parser::expectPeek(const TokenType &type) {
  if (peekTokenIs(type)) {
    nextToken();
    return true;
  }
  return false;
}

std::unique_ptr<ast::LetStatement> Parser::parseLetStatement() {
  Token let_token = m_cur_token;

  if (!expectPeek(TokenType::_IDENTIFIER)) {
    return nullptr;
  }

  std::shared_ptr<ast::Identifier> identifier_ptr =
      std::make_shared<ast::Identifier>(m_cur_token, m_cur_token.m_value);

  if (!expectPeek(TokenType::_ASSIGN)) {
    return nullptr;
  }

  // TODO: Temporarily, we skip expressions until we find a
  // semicolon just to pass unit tests.
  while (!curTokenIs(TokenType::_SEMICOLON)) {
    nextToken();
  }

  // TODO: Temporarily, we set Expression value_ptr to nullptr.
  return std::make_unique<ast::LetStatement>(let_token, identifier_ptr,
                                             nullptr);
}
