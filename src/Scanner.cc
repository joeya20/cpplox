#include "Scanner.hh"
#include "DiagManager.hh"
#include "Token.hh"
#include <vector>

Scanner::Scanner(std::string src, DiagManager& diagManager)
 : diagManager(diagManager) {
  this->source = src;
}

const std::unordered_map<std::string, Token::TokenType> Scanner::keywords = {
  {"and",    Token::TokenType::AND},
  {"class",  Token::TokenType::CLASS},
  {"else",   Token::TokenType::ELSE},
  {"false",  Token::TokenType::FALSE},
  {"for",    Token::TokenType::FOR},
  {"fun",    Token::TokenType::FUN},
  {"if",     Token::TokenType::IF},
  {"nil",    Token::TokenType::NIL},
  {"or",     Token::TokenType::OR},
  {"print",  Token::TokenType::PRINT},
  {"return", Token::TokenType::RETURN},
  {"super",  Token::TokenType::SUPER},
  {"this",   Token::TokenType::THIS},
  {"true",   Token::TokenType::TRUE},
  {"var",    Token::TokenType::VAR},
  {"while",  Token::TokenType::WHILE}
};

bool Scanner::isAtEnd() {
  return current >= source.length();
}

// advances to the next character in source
char Scanner::advance() {
  return source[current++];
}

std::vector<Token>& Scanner::scanTokens() {
  while (!isAtEnd()) {
    // We are at the beginning of the next lexeme.
    start = current;
    scanToken();
  }

  tokens.push_back(Token{Token::TokenType::EOF_, "", line});
  return tokens;
}

void Scanner::addToken(Token::TokenType type) {
  std::string text = source.substr(start, current);
  tokens.push_back(Token{type, text, line});
}

// returns the next character to be consumed
char Scanner::peek() {
  if (isAtEnd()) return '\0';
  return source[current];
}

char Scanner::lookAhead() {
  if(current + 1 > source.length()) return '\0';
  return source[current + 1];
}

// returns true and consumes the character
// if the next character in source matches expected
bool Scanner::match(char expected) {
  if (peek() != expected) return false;
  current++;
  return true;
}

void Scanner::scanToken() {
  char c = advance();
  switch (c) {
    case '(': addToken(Token::TokenType::LEFT_PAREN); break;
    case ')': addToken(Token::TokenType::RIGHT_PAREN); break;
    case '{': addToken(Token::TokenType::LEFT_BRACE); break;
    case '}': addToken(Token::TokenType::RIGHT_BRACE); break;
    case ',': addToken(Token::TokenType::COMMA); break;
    case '.': addToken(Token::TokenType::DOT); break;
    case '-': addToken(Token::TokenType::MINUS); break;
    case '+': addToken(Token::TokenType::PLUS); break;
    case ';': addToken(Token::TokenType::SEMICOLON); break;
    case '*': addToken(Token::TokenType::STAR); break;
    case '!':
      addToken(match('=') ? 
        Token::TokenType::BANG_EQUAL : 
        Token::TokenType::BANG);
      break;
    case '=':
      addToken(match('=') ? 
        Token::TokenType::EQUAL_EQUAL : 
        Token::TokenType::EQUAL);
      break;
    case '<':
      addToken(match('=') ? 
        Token::TokenType::LESS_EQUAL : 
        Token::TokenType::LESS);
      break;
    case '>':
      addToken(match('=') ? 
        Token::TokenType::GREATER_EQUAL : 
        Token::TokenType::GREATER);
      break;
    case '/':
      if (match('/')) {
        // A comment goes until the end of the line.
        while (peek() != '\n' && !isAtEnd()) advance();
      } else {
        addToken(Token::TokenType::SLASH);
      }
      break;
    case '"': 
      handleString(); 
      break;
    // Ignore whitespace.
    case ' ':
    case '\r':
    case '\t':
      break;
    // increment line on newline
    case '\n':
      line++;
      break;
    default:
      if(isNum(c)) {
        handleNum();
      }
      else if (isAlpha(c)) {
        handleIdent();
      }
      else {
        // TODO: terminal handling
        diagManager.handleError("Unexpected character: " + std::string{c}, line);
        break;
      }
  }
}

bool Scanner::isNum(char c) {
  return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
            c == '_';
}

bool Scanner::isAlphaNum(char c){
  return isAlpha(c) || isNum(c);
}

void Scanner::handleString() {
    // keep consuming until we hit EOS or EOF
    while (peek() != '"' && !isAtEnd()) {
      if (peek() == '\n') line++;
      advance();
    }
    // check for error
    if (isAtEnd()) {
      diagManager.handleError("Unterminated string.", line);
      return;
    }
    // The closing ".
    advance();
    // Trim the surrounding quotes.
    addToken(Token::TokenType::STRING);
}

void Scanner::handleNum() {
  // consume until we hit non-number
  while(isNum(peek())){
    advance();
  }
  // check if there is a decimal part
  if(peek() == '.') {
    if(isNum(lookAhead())) {
      advance();
      while(isNum(peek())) {
        advance();
      }
    }
    else {
      diagManager.handleError("Invalid number literal", line);
    }
  }
  addToken(Token::TokenType::NUMBER);
}

void Scanner::handleIdent() {
  while(isAlphaNum(peek()) && !isAtEnd()) {
    advance();
  }
  // check if its a keyword
  // this can also be done during AST creation, I think
  auto val = source.substr(start, current);
  if (auto kw = keywords.find(val); kw != keywords.end()) {
    addToken(kw->second);
  }
  else {
    addToken(Token::TokenType::IDENTIFIER);
  }
}
