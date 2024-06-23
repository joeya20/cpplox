#pragma once

#include <string>
#include "Reporter.hh"

int main(int argc, char* argv[]);
void runFile(std::string path, Reporter& reporter);
void runConsole(Reporter& reporter);
void run(std::string prog, Reporter& reporter);
