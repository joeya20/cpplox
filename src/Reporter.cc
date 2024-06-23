#include <iostream>
#include "Reporter.hh"

void Reporter::handleError(std::string message, bool terminal) {
  std::cout << "Error: " << message << "\n";
  if (terminal) {
    std::exit(EXIT_FAILURE);
  }
}


void Reporter::handleError(std::string message, uint32_t lineno, bool terminal) {
  std::cout << "[line " << lineno << "] Error: " << message << "\n";
  if (terminal) {
    std::exit(EXIT_FAILURE);
  }
}

void Reporter::handleWarning(std::string message) {
  std::cout << "Warning: " << message << "\n";
  this->numWarnings += 1;
}
