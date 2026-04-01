#include <iostream>
#include <exception>
#include "Server.hpp"
#include "parseConf.hpp"

int main(int argc, char *argv[]) {
    if (argc > 2) {
        std::cerr << "Usage: ./webserv [file.conf]" << std::endl;
        return 1;
    }
    Server server;
    std::string fileName = argc == 1 ? "default.conf" : argv[1];
    try {
        parseConf(fileName);
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}