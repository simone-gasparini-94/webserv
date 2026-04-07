#include <iostream>
#include <fstream>
#include <stack>
#include <stdexcept>
#include <cctype>
#include "Block.hpp"

bool isClosing(std::string line) {
    size_t pos = line.find("}");
    if (pos == line.npos) return false;
    for (size_t i = 0; i < line.length(); i++) {
        if (i == pos) continue;
        if (!isspace(line[i])) throw std::runtime_error("Error: invalid token");
    }
    return true;
}

void checkOnlySpaces(std::string line, size_t start, size_t end) {
    if (start > end) throw std::runtime_error("Error: parsing failure");
    for (size_t i = start; i < end; i++) {
        if (!isspace(line[i])) throw std::runtime_error("Error: invalid token");
    }
}

bool isOpening(std::string line) {
    size_t pos = line.find("{");
    if (pos == line.npos) return false;
    checkOnlySpaces(line, pos + 1, line.length());
    return true;
}


void checkEndPoint(std::string line, size_t start, size_t end) {
    if (start > end) throw std::runtime_error("Error: parsing failure");
    bool found = false;
    for (size_t i = start; i < end; i++) {
        if (!isspace(line[i])) {
            if (line[i] != '/') throw std::runtime_error("Error: invalid location's endpoint");
            found = true;
            while (i < end && !isspace(line[i])) i++;
            while (i < end) {
                if (!isspace(line[i])) {
                    throw std::runtime_error("Error: invalid token");
                }
                i++;
            }
        }
    }
    if (!found) throw std::runtime_error("Error: location's endpoint not specified");
}

void checkBetweenDirectiveAndBrace(std::string line, size_t start, size_t end, std::string type) {
    if (start > end) throw std::runtime_error("Error: parsing failure");
    if (type == "server") {
        checkOnlySpaces(line, start, end);
    } else if (type == "location") {
        checkEndPoint(line, start, end);
    }
}

bool isBlock(std::string line, std::string keyword) {
    size_t pos = line.find(keyword);
    if (pos == line.npos) return false;
    checkOnlySpaces(line, 0, pos);
    size_t start = pos + keyword.length();
    size_t end = line.find("{");
    if (keyword == "server") {
        checkBetweenDirectiveAndBrace(line, start, end, "server");
    } else if (keyword == "location") {
        checkBetweenDirectiveAndBrace(line, start, end, "location");
    }
    return true;
}

bool isNotEmpty(std::string line) {
    for (size_t i = 0; i < line.length(); i++) {
        if (!isspace(line[i])) return true;
    }
    return false;
}

void parseDirective(std::string &line, Block &block) {
    (void)line;
    (void)block;
}

void storeEndPoint(LocationBlock &location, std::string line) {
    size_t start = line.find("location");
}

void parseDirectives(Block &block, std::ifstream &file, int level) {
    if (level == 3) return;
    if (level != block.type) throw std::runtime_error("Error: invalid token");
    std::string line;
    while (std::getline(file, line)) {
        if (isClosing(line)) {
            return;
        } else if (isOpening(line)) {
            if (isBlock(line, "server")) {
                ServerBlock server;
                parseDirectives(server, file, level + 1);
                block.add(server);
            } else if (isBlock(line, "location")) {
                LocationBlock location;
                storeEndPoint(location, line);
                parseDirectives(location, file, level + 1);
                block.add(location);
            } else {
                throw std::runtime_error("Error: invalid token");
            }
        } else if (isNotEmpty(line)) {
            parseDirective(line, block);
        }
    }
}