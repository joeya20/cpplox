#pragma once

#include <string>
#include <vector>
#include "Reporter.hh"
#include "Token.hh"

class Scanner {
  std::vector<Token> tokens;
public:
  Scanner(std::string prog, Reporter& reporter);
  std::vector<Token>& getTokens();
};
