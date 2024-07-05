#pragma once

#include <string>
#include "DiagManager.hh"

int main(int argc, char* argv[]);
void runFile(std::string path, DiagManager& diagManager);
void runConsole(DiagManager& diagManager);
void run(std::string prog, DiagManager& diagManager);
