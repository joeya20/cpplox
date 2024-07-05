#include <iostream>
#include "Reporter.hh"

void Reporter::handleError(std::string message) {
  std::cout << "Error: " << message << "\n";
}

void Reporter::handleError(std::string message, int lineno) {
  std::cout << "[line " << lineno << "] Error: " << message << "\n";
}

void Reporter::handleWarning(std::string message) {
  std::cout << "Warning: " << message << "\n";
  this->numWarnings += 1;
  if(this->numWarnings > 15) {
    handleError("Too many warnings (> 15) encountered.");
  }
}

bool Reporter::hasErrors() {
  return this->errors.size() > 0;
}

void reportErrors()