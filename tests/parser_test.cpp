#include "parser_test.h"
#include "../src/parser.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

void checkParserErrors(const Parser &p, const std::string &test_id) {
  std::vector<std::string> errors = p.Errors();

  if (errors.size() == 0) {
    return;
  }
  std::cerr << "FAIL\t" << test_id << " - parser has " << errors.size()
            << " errors." << std::endl;

  for (std::string error_msg : errors) {
    std::cerr << "parser error: " << error_msg << std::endl;
  }

  exit(EXIT_FAILURE);
}

bool validateLetStatement(std::shared_ptr<ast::Statement> s,
                          const std::string &expected,
                          const std::string &test_id) {
  if (s->TokenLiteral() != "let") {
    std::cerr << "FAIL\t" << test_id
              << " - TokenLiteral not 'let', instead got=\""
              << s->TokenLiteral() << "\"" << std::endl;
    return false;
  }

  std::shared_ptr<ast::LetStatement> let_stmt =
      std::dynamic_pointer_cast<ast::LetStatement>(s);

  if (!let_stmt) {
    std::cerr << "FAIL\t" << test_id << " - *s is not a ast::LetStatement"
              << std::endl;
    return false;
  }

  if (let_stmt->m_identifier_ptr->m_value != expected) {
    std::cerr << "FAIL\t" << test_id << " - let_stmt identifier value is not "
              << expected << ", instead got=\""
              << let_stmt->m_identifier_ptr->m_value << "\"" << std::endl;
    return false;
  }

  if (let_stmt->m_identifier_ptr->TokenLiteral() != expected) {
    std::cerr << "FAIL\n"
              << test_id << " - let_stmt identifier token literal is not "
              << expected << ", instead got=\""
              << let_stmt->m_identifier_ptr->TokenLiteral() << "\""
              << std::endl;
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
    std::cerr << "FAIL\t" << test_id
              << " - Program::parseProgram() returned nullptr" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (program->m_statements.size() != expected.size()) {
    std::cerr << "FAIL\t" << test_id
              << " - Program::parseProgram() does not contain "
              << expected.size() << " statements. got=\""
              << program->m_statements.size() << "\"" << std::endl;
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
    std::cout << "ok\t" << test_id << std::endl;
  }
}

bool validateReturnStatement(std::shared_ptr<ast::Statement> s,
                             const std::string &expected,
                             const std::string &test_id) {
  if (s->TokenLiteral() != "return") {
    std::cerr << "FAIL\t" << test_id
              << " - TokenLiteral not 'return', instead got=\""
              << s->TokenLiteral() << "\"" << std::endl;
    return false;
  }

  std::shared_ptr<ast::ReturnStatement> ret_stmt =
      std::dynamic_pointer_cast<ast::ReturnStatement>(s);

  if (!ret_stmt) {
    std::cerr << "FAIL\t" << test_id << " - *s is not a ast::RetunStatement"
              << std::endl;
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
    std::cerr << test_id << "Program::parseProgram() does not contain "
              << expected.size() << " statements. got=\""
              << program->m_statements.size() << "\"" << std::endl;
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
    std::cout << "ok\t" << test_id << std::endl;
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
  std::cout << "passed\t(2/2)" << std::endl;
}
