#include "webserv.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./webserv <config file>" << std::endl;
    return 1;
  }
  std::ifstream configFile;
  std::string fileName = argv[1];
  checkExtension(fileName);
  readFile(configFile, fileName);
  MainBlock main;
  parseDirectives(main, configFile, 0);

  // join by deciding how to design Server class 

  Server server(PORT);
  try {
    server.init();
    server.run();
  } catch (const std::exception &e) {
    LOG_ERROR << e.what();
    return 1;
  }
  return 0;
}
