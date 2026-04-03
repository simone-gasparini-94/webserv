#ifndef DEFINES_HPP
#define DEFINES_HPP

// Macros
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define CYAN "\033[36m"

// Constants
const int PORT = 8080;

// Enums
enum status { SUCCESS = 0, FAILURE = 1, ERROR = -1, DEBUG, INFO };

#endif
