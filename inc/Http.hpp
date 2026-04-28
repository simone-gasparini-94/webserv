#ifndef HTTP_HPP
# define HTTP_HPP

#include <cstddef>
#include <iostream>
#include <sstream>

class HttpRequest {
public:
    std::string method;
    std::string version;
    std::string contentType;
    std::size_t contentLength;
    std::string body;
    HttpRequest();
    HttpRequest(std::string rawString);
};

std::string parseMethod(std::string &line);
std::string parseVersion(std::string &line);
std::string parseContent(std::string &line);
std::string parseBody(std::istringstream &stream);

#endif
