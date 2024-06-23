#include <sstream>
#include "Token.hh"


const std::string Token::tokenName[] = {
  "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
  "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", 
  "STAR", "NOT", "NOT_EQUAL", "EQUAL", "EQUAL_EQUAL", 
  "GREATER", "GREATER_EQUAL", "LESS", "LESS_EQUAL",
  "IDENTIFIER", "STRING", "NUMBER", "AND", "CLASS", "ELSE",
  "FALSE", "FUN", "FOR", "IF", "NIL", "OR", "PRINT", 
  "RETURN", "SUPER", "THIS", "TRUE", "VAR", "WHILE", "EOF_"
};

Token::Token(Token::TokenType type, std::string lexeme, int lineno) {
  this->lineno = lineno;
  this->lexeme = lexeme;
  this->type = type;
}

std::string Token::toString() {
  std::stringstream ss;
  ss << this->typeString() << " " << this->lexeme;
  return ss.str();
}

std::string Token::typeString() {
  return Token::tokenName[int(this->type)];
}

Token::TokenType Token::getType() {
  return this->type;
}
