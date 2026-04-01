#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#define EXT_LEN 5

void checkExtension(std::string fileName) {
    size_t length = fileName.size();
    std::string ext = ".conf";
    if (length < EXT_LEN || fileName.substr(length - EXT_LEN, EXT_LEN) != ext) {
        throw std::runtime_error("Error: Invalid extension");
    }
}

void parseConf(std::string fileName) {
    checkExtension(fileName);
    std::ifstream confFile(fileName.c_str());
}