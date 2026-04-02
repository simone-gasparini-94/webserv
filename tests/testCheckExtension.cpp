#include <iostream>
#include <exception>
#include "parseConf.hpp"

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"


void testCheckExtension(int N, std::string argument, std::string string) {
    std::string failure = "checkExtension(\"" + argument + "\")  -->  " + RED + "FAIL" + RESET;
    std::string success = "checkExtension(\"" + argument + "\")  -->  " + GREEN + "SUCCESS" + RESET;
    std::string pass;
    std::string except;
    if (string == "throw") {
        pass = failure;
        except = success;
    } else {
        pass = success;
        except = failure;
    }
    try {
        checkExtension(argument);
        std::cout << N << ": " << pass << std::endl;
    } catch (std::exception &e) {
        std::cout << N << ": " << except << std::endl;
    }
}

int main() {
    testCheckExtension(1, "", "throw");
    testCheckExtension(2, "wrong", "throw");
    testCheckExtension(3, "text.txt", "throw");
    testCheckExtension(4, "conf", "throw");
    testCheckExtension(5, ".conf", "pass");
    testCheckExtension(6, "nginx.conf", "pass");
    testCheckExtension(7, "server.conf", "pass");
    testCheckExtension(8, "something.conff", "throw");
    testCheckExtension(9, "else.con", "throw");
    testCheckExtension(10, "config", "throw");
}