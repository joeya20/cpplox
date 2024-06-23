#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "Reporter.hh"
#include "Token.hh"

class Scanner {
  std::string source;
  std::vector<Token> tokens;
  Reporter& reporter;
  static const std::unordered_map<std::string, Token::TokenType> keywords;

  int start = 0;
  int current = 0;
  int line = 1;

  bool isAtEnd();
  void scanToken();
  char peek();
  char lookAhead();
  char advance();
  void addToken(Token::TokenType);
  bool match(char expected);
  void handleString();
  void handleNum();
  void handleIdent();
  bool isNum(char c);
  bool isAlpha(char c);
  bool isAlphaNum(char c);

public:
  Scanner(std::string, Reporter&);
  std::vector<Token>& scanTokens();
};
