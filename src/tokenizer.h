// tokenizer.h
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"
#include <optional>
#include <string>
#include <vector>
#include <map>

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

  /* std::map of existing keywords to its corresponding TokenType. */
  const std::map<std::string, TokenType> keywords = {
      {"fn", TokenType::_FUNCTION},
      {"let", TokenType::_LET},
  };

  /* Incoming source code to compile in string. */
  const std::string m_src;

  /**
   * @brief Reads the next character and consumes it.
   */
  void readChar();


  /**
   * @brief Gets the std::string of the current token pointed by m_cursor
   * @return std::string of the current token
   */
  std::string readIdentifier();

  /**
   * @brief Gets the std::string of the current token pointed by m_cursor (numeric)
   * @return std::string of the current token (digits only)
   */
  std::string readDigits();

  /**
   * @brief Finds the TokenType of the input string.
   *
   * Takes an input string (where its first character is alnum or '_'),
   * retunrs the TokenType of the string.
   *
   * @param input The input string.
   * @return TokenType of the input string.
   */
  TokenType lookupIdentifier(std::string input);

  /**
   * @brief Skips and consumes whitespace characters.
   */
  void skipWhitespace();
};

#endif

