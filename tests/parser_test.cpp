#include "parser_test.h"
#include "../src/parser.h"
#include "../utils/msg_fmt.h"
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

void checkParserErrors(const Parser &p, const std::string &test_id) {
  std::vector<std::string> errors = p.Errors();

  if (errors.size() == 0) {
    return;
  }
  msg::Error("parser has " + std::to_string(errors.size()) + " errors.",
             test_id);

  for (std::string error_msg : errors) {
    msg::Error("parser error: " + error_msg, test_id);
  }

  exit(EXIT_FAILURE);
}

bool validateLetStatement(std::shared_ptr<ast::Statement> s,
                          const std::string &expected,
                          const std::string &test_id) {
  if (s->TokenLiteral() != "let") {
    msg::Fatal("TokenLiteral not 'let', instead got=\"" + s->TokenLiteral() +
                   "\"",
               test_id);
    return false;
  }

  std::shared_ptr<ast::LetStatement> let_stmt =
      std::dynamic_pointer_cast<ast::LetStatement>(s);

  if (!let_stmt) {
    msg::Fatal("*s is not an ast::LetStatement", test_id);
    return false;
  }

  if (let_stmt->m_identifier_ptr->m_value != expected) {
    msg::Fatal("expected let_stmt identifier value \"" + expected +
                   "\", instead got=\"" + let_stmt->m_identifier_ptr->m_value +
                   "\"",
               test_id);
    return false;
  }

  if (let_stmt->m_identifier_ptr->TokenLiteral() != expected) {
    msg::Fatal("expected let_stmt identifier TokenLiteral() \"" + expected +
                   "\", instead got=\"" +
                   let_stmt->m_identifier_ptr->TokenLiteral() + "\"",
               test_id);
    return false;
  }

  return true;
}

void TestLetStatements(std::string input,
                       const std::vector<std::string> expected, int tc) {
  Tokenizer t(input);
  Parser p(t);
  ast::Program *program = p.parseProgram();

  std::string test_id = "let_statement_test[" + std::to_string(tc) + "]";
  checkParserErrors(p, test_id);

  if (program == nullptr) {
    msg::Fatal("Program::parseProgram() returned nullptr", test_id);
    exit(EXIT_FAILURE);
  }

  if (program->m_statements.size() != expected.size()) {
    msg::Fatal("expected Program::parserProgram() to contain " +
                   std::to_string(expected.size()) + " statements. got=\"" +
                   std::to_string(program->m_statements.size()) + "\"",
               test_id);
    exit(EXIT_FAILURE);
  }

  bool passed = true;
  for (int i = 0; i < expected.size(); i++) {
    std::shared_ptr<ast::Statement> stmt = program->m_statements[i];
    if (!validateLetStatement(stmt, expected[i], test_id)) {
      passed = false;
    }
  }

  if (passed) {
    msg::Ok(test_id);
  }
}

bool validateReturnStatement(std::shared_ptr<ast::Statement> s,
                             const std::string &expected,
                             const std::string &test_id) {
  if (s->TokenLiteral() != "return") {
    msg::Fatal("TokenLiteral not 'return', instead got=\"" + s->TokenLiteral() +
                   "\"",
               test_id);
    return false;
  }

  std::shared_ptr<ast::ReturnStatement> ret_stmt =
      std::dynamic_pointer_cast<ast::ReturnStatement>(s);

  if (!ret_stmt) {
    msg::Fatal("*s is not an ast::ReturnStatement", test_id);
    return false;
  }

  return true;
}

void TestReturnStatements(std::string input,
                          const std::vector<std::string> expected, int tc) {
  Tokenizer t(input);
  Parser p(t);

  ast::Program *program = p.parseProgram();

  std::string test_id = "return_statement_test[" + std::to_string(tc) + "] ";
  checkParserErrors(p, test_id);

  if (program->m_statements.size() != expected.size()) {
    msg::Fatal("Program::parseProgram() does not contain " +
                   std::to_string(expected.size()) + " statements. got=\"" +
                   std::to_string(program->m_statements.size()) + "\"",
               test_id);
    exit(EXIT_FAILURE);
  }

  bool passed = true;
  for (int i = 0; i < expected.size(); i++) {
    std::shared_ptr<ast::Statement> stmt = program->m_statements[i];
    if (!validateReturnStatement(stmt, expected[i], test_id)) {
      passed = false;
    }
  }

  if (passed) {
    msg::Ok(test_id);
  }
}

// ====================================================================================
//                                       Testcases
// ====================================================================================

void LetStatementTest1() {
  std::string input = R"(
  let x = 5;
  let y = 10;
  let foobar = 838383;
  )";

  std::vector<std::string> expected = {"x", "y", "foobar"}; // identifiers
  TestLetStatements(input, expected, 1);
}

void LetStatementTest2() { // parsing error test case
  std::string input = R"(
  let x 5;
  let = 10;
  let 838383;
  )";

  std::vector<std::string> expected = {"x", "y", "foobar"}; // identifiers
  TestLetStatements(input, expected, 2);
}

void ReturnStatementTest1() {
  std::string input = R"(
  return 5;
  return 10;
  return 123321;
  )";

  std::vector<std::string> expected = {"x", "y", "foobar"};
  TestReturnStatements(input, expected, 1);
}

void RunParserTests() {
  LetStatementTest1();
  // LetStatementTest2();
  ReturnStatementTest1();
}
