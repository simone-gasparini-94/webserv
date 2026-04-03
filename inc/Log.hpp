#ifndef LOG_HPP
#define LOG_HPP

#include "defines.hpp"
#include <sstream>
#include <string>
#include <fstream>

class Log {

public:
  Log(status);
  ~Log();

  static void setLogFile(const std::string &filename);

  template <typename T> Log &operator<<(const T &msg) {
    _ss << msg;
    return *this;
  }

private:
  status _level;
  std::stringstream _ss;

  static std::ofstream _fileStream;

  static void log(status level, const std::string &msg);

  // Rest of OFC
  Log();
  Log(Log const &);
  Log &operator=(Log const &);
};

#endif
