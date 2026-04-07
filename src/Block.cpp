#include "Block.hpp"

// BASE CLASS
Block::Block(enum BlockType BlockType)
: type(BlockType), root("/") {}

// LOCATION 
Location::Location()
: Block(LOCATION), endpoint("/") {}

void Location::addChild(Block &block) {
    (void)block;
}

void Location::addListen(size_t port) {
    (void)port;
}

// SERVER
Server::Server()
: Block(SERVER), listen(8080) {}

void Server::addChild(Block &block) {
    locations.push_back(static_cast<Location&>(block));
}

void Server::addListen(size_t port) {
    this->listen = port;
}

// MAIN
Main::Main()
: Block(MAIN) {}

void Main::addChild(Block &block) {
    server = static_cast<Server&>(block);
}

void Main::addListen(size_t port) {
    (void)port;
}
