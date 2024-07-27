#include "tokenizer.h"

[[nodiscard]] std::optional<char> Tokenizer::peak(int ahead) const {
  if (m_idx + ahead <= m_src.size()) {
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
    if (std::isalpha(peak().value())) {
        buf.push_back(consume());
    }
  }
  return tokens;
}
