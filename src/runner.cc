#include "Reporter.hh"
#include "runner.hh"
#include <sstream>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include "Scanner.hh"
#include "Token.hh"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  Reporter reporter {};

  if(argc > 2) {
    reporter.handleError("Expected 1 argument", true);
  }
  else if (argc == 2) {
    std::string filepath = std::string{argv[1]};
    if(!fs::exists(filepath)) {
      reporter.handleError("Invalid path provided, file does not exist", true);
    }
    if(!fs::is_regular_file(filepath)) {
      reporter.handleError("Invalid path provided, not a file", true);
    }
    runFile(filepath, reporter);
  }
  else {
    runConsole(reporter);
  }

  return 0;
}

void runFile(std::string path, Reporter& reporter) {
  std::ifstream ifs(path);
  std::stringstream buffer;
  buffer << ifs.rdbuf();
  run(buffer.str(), reporter);
}

void runConsole(Reporter& reporter) {
  std::string cmd;
  std::cout << "> ";
  while(std::getline(std::cin, cmd)) {
    run(cmd, reporter);
  }
}

void run(std::string prog, Reporter& reporter) {
  Scanner scanner{prog, reporter};
  std::vector<Token>& tokens  = scanner.getTokens();

  for(auto& token : tokens) {
    std::cout << "Token: " << token.lexeme() << "\n";
  }
}
