#include "Server.hpp"
#include "Log.hpp"
#include "defines.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

// public ----------------------------------------------------------------------

// setting fd to -1, so the destructor ignores uninitialized fds
Server::Server(int port) : _port(port), _serverFd(-1) {
  std::memset(&_address, 0, sizeof(_address));
}

Server::~Server() {
  if (_serverFd != -1) {
    Log(INFO) << "Closing server socket";
    close(_serverFd);
  }
}

// methods
void Server::init() {

  Log::setLogFile("webserv.log");

  _serverFd = socket(AF_INET, SOCK_STREAM, 0);
  if (_serverFd == ERROR)
    throw std::runtime_error("Socket creation failed");

  _address.sin_family = AF_INET;
  _address.sin_port = htons(_port);
  _address.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(_serverFd, (struct sockaddr *)&_address, sizeof(_address)) == ERROR) {
    close(_serverFd);
    _serverFd = -1;
    throw std::runtime_error("Bind failed");
  }

  if (listen(_serverFd, 10) == ERROR) {
    close(_serverFd);
    _serverFd = -1;
    throw std::runtime_error("Listen failed");
  }

  Log(INFO) << "Server is listening on port " << _port;
}

void Server::run() {
  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  char buffer[1024];

  while (true) {
    clientAddrLen = sizeof(clientAddr);
    int newSocket =
        accept(_serverFd, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (newSocket == ERROR) {
      Log(ERROR) << "Failed to accept connection.";
      continue;
    }
    Log(INFO) << "Connection accepted!";

    std::memset(buffer, 0, sizeof(buffer));
    int bytesRead = read(newSocket, buffer, sizeof(buffer) - 1);
    if (bytesRead > 0) {
      std::cout << buffer << std::endl;
    }
    std::string httpResponse =
        "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: "
        "12\r\n\r\nHello World!";
    write(newSocket, httpResponse.c_str(), httpResponse.length());
    close(newSocket);
    Log(INFO) << "Connection closed!";
  }
}

// private ---------------------------------------------------------------------
// int _port;
// int _serverFd;
// struct sockaddr_in _address;
