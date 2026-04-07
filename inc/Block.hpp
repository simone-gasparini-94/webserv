#ifndef BLOCK_HPP
# define BLOCK_HPP

#include <string>
#include <vector>

enum BlockType {
    MAIN,
    SERVER,
    LOCATION
};

class Block {
public:
    enum BlockType type;
    std::string root;

    Block(enum BlockType type);
    virtual ~Block() {}

    virtual void addChild(Block &block) = 0;
    virtual void addListen(size_t port) = 0;
};

class Location: public Block {
public:
    std::string endpoint;

    Location();

    void addChild(Block &block);
    void addListen(size_t port);
};

class Server: public Block {
public:
    size_t listen;
    std::vector<Location> locations; 

    Server();

    void addChild(Block &block);
    void addListen(size_t port);
};

class Main: public Block {
public:
    Server server;

    Main();

    void addChild(Block &block);
    void addListen(size_t port);
};

#endif