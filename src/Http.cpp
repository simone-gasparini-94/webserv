#include "Http.hpp"

HttpRequest::HttpRequest() : method(""), version(""), contentType(""), contentLength(0), body("") {}

HttpRequest::HttpRequest(std::string str) {
    std::string line;
    std::istringstream stream(str);
    int i = 0;
    while (std::getline(stream, line)) {
        if (i == 0) {
            method = parseMethod(line);
            version = parseVersion(line);
        } else if (line.find("Content-Type: ") != std::string::npos) {
            contentType = parseContent(line);
        } else if (line.find("Content-Length: ") != std::string::npos) {
            std::string str = parseContent(line);
            std::istringstream(str) >> contentLength;
        } else if (line.find("\r") == 0) {
            body = parseBody(stream);
        }
        i++;
    }
}

std::string parseMethod(std::string &line) {
    std::istringstream stream(line);
    std::string method;
    std::string slash;
    std::string version;
    stream >> method >> slash >> version;
    return method;
}

std::string parseVersion(std::string &line) {
    std::istringstream stream(line);
    std::string method;
    std::string slash;
    std::string version;
    stream >> method >> slash >> version;
    return version;
}

std::string parseContent(std::string &line) {
    std::istringstream linestream(line);
    std::string text;
    std::string content;
    linestream >> text >> content;
    return content;
}

std::string parseBody(std::istringstream &stream) {
    std::string line;
    std::string body = "";
    while (std::getline(stream, line)) {
        body.append(line + "\n");
    }
    if (body.size() > 0) body.erase(body.size() - 1);
    return body;
}
