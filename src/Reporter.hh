#pragma once

#include <string>

class Reporter {
  private:
    int numWarnings;

  public:
    void handleError(std::string message, bool terminal);
    void handleError(std::string message, int lineno, bool terminal);
    void handleWarning(std::string message);
};
