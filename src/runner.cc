#include "DiagManager.hh"
#include "runner.hh"
#include <cstdlib>
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

  DiagManager diagManager {};

  if(argc > 2) {
    std::cerr << "Expected 1 argument, got " << argc << "\n";
    exit(EXIT_FAILURE);
  }
  else if (argc == 2) {
    std::string filepath = std::string{argv[1]};
    if(!fs::exists(filepath)) {
      std::cerr << "Invalid path provided, file does not exist\n";
      exit(EXIT_FAILURE);
    }
    if(!fs::is_regular_file(filepath)) {
      std::cerr << "Invalid path provided, not a file\n";
      exit(EXIT_FAILURE);
    }
    runFile(filepath, diagManager);
  }
  else {
    runConsole(diagManager);
  }

  return 0;
}

void runFile(std::string path, DiagManager& diagManager) {
  std::ifstream ifs(path);
  std::stringstream buffer;
  buffer << ifs.rdbuf();
  run(buffer.str(), diagManager);

  // report warnings and errors
  diagManager.report();
  // exit if we encounter any errors
  if(diagManager.hasErrors()) {
    exit(EXIT_FAILURE);
  }
}

void runConsole(DiagManager& diagManager) {
  std::string cmd;
  std::cout << ">> ";
  while(std::getline(std::cin, cmd)) {
    run(cmd, diagManager);
    // report warnings / errors and clear them
    diagManager.report();
    diagManager.clear();
    std::cout << ">> ";
  }
}

void run(std::string prog, DiagManager& diagManager) {
  Scanner scanner{prog, diagManager};
  std::vector<Token>& tokens  = scanner.scanTokens();

  for(auto& token : tokens) {
    std::cout << "Token: " << token.toString() << "\n";
  }
}
