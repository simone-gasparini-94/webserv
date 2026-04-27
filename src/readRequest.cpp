#include <iostream>
#include <stdexcept>
#include <sstream>
#include <unistd.h>
#include "Http.hpp"

#define BUF_SIZE 4

size_t getContentLength(std::string request) {
    size_t contentLength = 0;
    std::string line;
    std::string text;
    std::istringstream stream(request);
    while (std::getline(stream, line)) {
        if (line.find("\r\n\r\n") != std::string::npos) break;
        if (line.find("Content-Length") != std::string::npos) {
            std::istringstream linestream(line);
            linestream >> text >> contentLength;
            break;
        }
    }
    return contentLength;
}

std::string readRequest(int fd) {
    std::string request;
    char buffer[BUF_SIZE];
    while (true) {
        int bytesRead = read(fd, buffer, BUF_SIZE - 1);
        if (bytesRead == -1) throw std::runtime_error("read() failed");
        if (bytesRead == 0) break;
        buffer[BUF_SIZE - 1] = '\0';
        request.append(buffer);
        if (request.find("\r\n\r\n") != std::string::npos) break;
    }
    size_t contentLength = getContentLength(request);
    std::cout << request << std::endl;
    std::cout << contentLength << std::endl;
    return request;
}
