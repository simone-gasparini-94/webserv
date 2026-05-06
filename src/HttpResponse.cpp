#include "Http.hpp"

HttpResponse::HttpResponse(): version("HTTP/1.1") {
    statuses["200"] = "OK";
    statuses["400"] = "BAD REQUEST";
    statuses["404"] = "NOT FOUND";
    statuses["405"] = "METHOD NOT ALLOWED";
}

void HttpResponse::generateResponse(std::string status) {
    response = version + " " + status + " " + statuses[status] + "\r\n";
}
