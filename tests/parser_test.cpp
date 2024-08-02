#include "parser_test.h"
#include "../src/parser.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

void checkParserErrors(const Parser &p) {
  std::vector<std::string> errors = p.Errors();

  if (errors.size() == 0) {
    return;
  }
  std::cerr << "parser has " << errors.size() << " errors." << std::endl;

  for (std::string error_msg : errors) {
    std::cerr << "parser error: " << error_msg << std::endl;
  }

  exit(EXIT_FAILURE);
}

bool validateLetStatement(Tokenizer &t, std::shared_ptr<ast::Statement> s,
                          const std::string &expected_identifier,
                          const std::string &test_id) {
  if (s->TokenLiteral() != "let") {
    std::cerr << test_id << "TokenLiteral not 'let', instead got=\""
              << s->TokenLiteral() << "\"" << std::endl;
    return false;
  }

  std::shared_ptr<ast::LetStatement> let_stmt =
      std::dynamic_pointer_cast<ast::LetStatement>(s);

  if (!let_stmt) {
    std::cerr << test_id << "*s is not a LetStatement" << std::endl;
    return false;
  }

  if (let_stmt->m_identifier_ptr->m_value != expected_identifier) {
    std::cerr << test_id << "let_stmt identifier value is not "
              << expected_identifier << ", instead got=\""
              << let_stmt->m_identifier_ptr->m_value << "\"" << std::endl;
    return false;
  }

  if (let_stmt->m_identifier_ptr->TokenLiteral() != expected_identifier) {
    std::cerr << test_id << "let_stmt identifier token literal is not "
              << expected_identifier << ", instead got=\""
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
  checkParserErrors(p);

  std::string test_id = "let_statement_test[" + std::to_string(tc) + "] - ";

  if (program == nullptr) {
    std::cerr << test_id << "Program::parseProgram() returned nullptr"
              << std::endl;
    exit(EXIT_FAILURE);
  }

  if (program->m_statements.size() != expected.size()) {
    std::cerr << test_id << "Program::parseProgram() does not contain "
              << expected.size() << " statements. got=\""
              << program->m_statements.size() << "\"" << std::endl;
    exit(EXIT_FAILURE);
  }

  bool passed = true;
  for (int i = 0; i < expected.size(); i++) {
    std::shared_ptr<ast::Statement> stmt = program->m_statements[i];
    if (!validateLetStatement(t, stmt, expected[i], test_id)) {
      passed = false;
    }
  }

  if (passed) {
    std::cout << test_id << "passed." << std::endl;
  }
}

void LetStatementTest1() {
  std::string input = R"(
  let x = 5;
  let y = 10;
  let foobar = 838383;
  )";

  std::vector<std::string> expected_identifier = {"x", "y", "foobar"};
  TestLetStatements(input, expected_identifier, 1);
}

void LetStatementTest2() {
  std::string input = R"(
  let x 5;
  let = 10;
  let 838383;
  )";

  std::vector<std::string> expected_identifier = {"x", "y", "foobar"};
  TestLetStatements(input, expected_identifier, 2);
}

void RunParserTests() {
  LetStatementTest1();
  // LetStatementTest2();
}
