#include "Http.hpp"
#include <fstream>
#include <sstream>

HttpResponse::HttpResponse(): version("HTTP/1.1"), server("webserv\r\n"), emptyLine("\r\n") {
    statuses["200"] = "OK";
    statuses["400"] = "BAD REQUEST";
    statuses["404"] = "NOT FOUND";
    statuses["405"] = "METHOD NOT ALLOWED";
}

void HttpResponse::generateResponse(std::string status) {
    std::ostringstream ss;
    ss << version << " " << status << " " << statuses[status] << "\r\n";
    ss << "Server: " << server;
    ss << "Content-Type: " << "text/html" << "\r\n";
    std::string fileName = std::string("www/") + status + ".html";
    std::ifstream file(fileName.c_str());
    body << file.rdbuf();
    ss << "Content-Length: " << body.str().size() << "\r\n";
    ss << emptyLine;
    ss << body.str();
    response = ss.str();
}
