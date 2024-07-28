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

  /* Returns the next token to read. */
  Token nextToken();

  /* Reads the source string, convert to a vector of tokens.
   */
  std::vector<Token> tokenize();

private:
  /* Current cursor in the file. */
  int m_cursor;

  /* Cursor that points to the next character in the input string. */
  int m_read_cursor;

  /* Current character pointed by the cursor. */
  char m_ch;

  /* Incoming source code to compile in string. */
  const std::string m_src;

  /* To read the next character and consume it.*/
  void readChar();
};

#endif
