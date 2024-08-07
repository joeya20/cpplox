#pragma once

#include <string>
#include <vector>

class DiagManager {
  private:
    int numWarnings;
    std::vector<std::pair<int, std::string>> warnings;
    std::vector<std::pair<int, std::string>> errors;

  public:
    bool hasErrors(); 
    void handleWarning(std::string message);
    void handleWarning(std::string message, int lineno);
    void handleError(std::string message);
    void handleError(std::string message, int lineno);
    void report();
    void clear();
    void clearErrors();
    void clearWarnings();
    void reportErrors();
    void reportWarnings();
};
