#include "tokenizer.h"
#include <cctype>
#include <cstdlib>
#include <iostream>

Tokenizer::Tokenizer(const std::string &src)
    : m_src(std::move(src)), m_idx(0){};

[[nodiscard]] std::optional<char> Tokenizer::peak(int ahead) const {
  if (m_idx + ahead > m_src.size()) {
    return {};
  } else {
    return m_src[m_idx];
  }
}

char Tokenizer::consume() { return m_src[m_idx++]; }

std::vector<Token> Tokenizer::tokenize() {

  std::vector<Token> tokens;
  std::string buf;

  while (peak().has_value()) {
    if (std::isspace(peak().value())) {
      consume();
      continue;
    }

    if (std::isalpha(peak().value())) {
      buf.push_back(consume());
      while (peak().has_value() && std::isalnum(peak().value())) {
        buf.push_back(consume());
      }

      if (buf == "exit") {
        tokens.emplace_back(TokenType::_EXIT);
      } else {
        std::cerr << "Exit Error!" << std::endl;
        exit(EXIT_FAILURE);
      }
      buf.clear();

    } else if (std::isdigit(peak().value())) {
      buf.push_back(consume());
      while (peak().has_value() && std::isdigit(peak().value())) {
        buf.push_back(consume());
      }
      tokens.emplace_back(TokenType::_INT_LITERAL, buf);
      buf.clear();

    } else if (peak().value() == ';') {
      consume();
      tokens.emplace_back(TokenType::_SEMICOLON);

    } else {
      std::cerr << "Unrecognized Error!" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  m_idx = 0;
  return tokens;
}
