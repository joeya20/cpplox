#include <iostream>
#include <sstream>
#include "DiagManager.hh"

void DiagManager::handleError(std::string message) {
  handleError(message, -1);
}

void DiagManager::handleError(std::string message, int lineno) {
  this->errors.push_back({lineno, message});
}

void DiagManager::handleWarning(std::string message) {
  handleWarning(message, -1);
}

void DiagManager::handleWarning(std::string message, int lineno) {
  this->numWarnings += 1;
  this->warnings.push_back({lineno, message});
  if(this->numWarnings > 15) {
    handleError("Too many warnings (> 15) encountered.");
  }
}

bool DiagManager::hasErrors() {
  return this->errors.size() > 0;
}

void DiagManager::report() {
  reportWarnings();
  reportErrors();
}

void DiagManager::reportWarnings() {
  std::stringstream ss;
  for (auto & warning : this->warnings) {
    if(warning.first != -1) {
      ss << "[line " << warning.first << "] ";
    }
    ss << "Warning: " << warning.second << "\n";
  }
  std::cout << ss.str() << std::endl;
}

void DiagManager::reportErrors() {
  std::stringstream ss;
  for (auto & error : this->errors) {
    if(error.first != -1) {
      ss << "[line " << error.first << "] ";
    }
    ss << "Error: " << error.second << "\n";
  }
  std::cout << ss.str() << std::endl;
}

void DiagManager::clearWarnings() {
  this->warnings.clear();
}

void DiagManager::clearErrors() {
  this->errors.clear();
}

void DiagManager::clear() {
  clearWarnings();
  clearErrors();
}
