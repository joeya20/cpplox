#pragma once
#include <string>
#include <cstdint>

class Reporter {
  private:
    int numWarnings;

  public:
    void handleError(std::string message, bool terminal);
    void handleError(std::string message, uint32_t lineno, bool terminal);
    void handleWarning(std::string message);
};
