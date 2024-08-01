#include "parser_test.h"
#include "../src/parser.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

void validateLetStatement(Tokenizer &t, Statement *s,
                          const std::string &expected_identifier,
                          const std::string &test_id) {
  if (s->TokenLiteral() != "let") {
    std::cerr << test_id
              << "TokenLiteral not 'let', instead got=" << s->TokenLiteral()
              << std::endl;
    exit(EXIT_FAILURE);
  }

  LetStatement *let_stmt = dynamic_cast<LetStatement *>(s);

  if (!let_stmt) {
    std::cerr << test_id << "*s is not a LetStatement" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (let_stmt->m_identifier_ptr->m_value != expected_identifier) {
    std::cerr << test_id << "let_stmt identifier value is not "
              << expected_identifier
              << ", instead got=" << let_stmt->m_identifier_ptr->m_value
              << std::endl;
    exit(EXIT_FAILURE);
  }

  if (let_stmt->m_identifier_ptr->TokenLiteral() != expected_identifier) {
    std::cerr << test_id << "let_stmt identifier token literal is not "
              << expected_identifier
              << ", instead got=" << let_stmt->m_identifier_ptr->TokenLiteral()
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

void TestLetStatements(std::string input,
                       const std::vector<std::string> expected, int tc) {
  Tokenizer t(input);
  Parser p(t);
  Program *program = p.parseProgram();
  std::string test_id = "let_statement_test[" + std::to_string(tc) + "] - ";
  if (program == nullptr) {
    std::cerr << test_id << "Program::parseProgram() returned nullptr"
              << std::endl;
    exit(EXIT_FAILURE);
  }

  if (program->m_statements.size() != expected.size()) {
    std::cerr << test_id << "Program::parseProgram() does not contain "
              << expected.size()
              << " statements. got=" << program->m_statements.size()
              << std::endl;
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < input.size(); i++) {
    Statement *stmt = program->m_statements[i];
    validateLetStatement(t, stmt, expected[i], test_id);
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

void RunParserTests() { LetStatementTest1(); }
