// tokenizer.h
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"
#include <optional>
#include <string>
#include <vector>

class Tokenizer {
public:
  Tokenizer(const std::string &src);

  /* Reads the source string, convert to a vector of tokens.
   */
  std::vector<Token> tokenize();

private:
  /* Current cursor in the file. */
  int m_idx;

  /* Incoming source code to compile in string. */
  const std::string m_src;

  /* Checks the next incoming character if it exists. */
  [[nodiscard]] std::optional<char> peak(int ahead = 1) const;

  /* Returns the next character and 'consumes' that character,
   * incrementing the index.
   */
  char consume();
};

#endif
