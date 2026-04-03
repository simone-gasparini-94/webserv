#include "Log.hpp"
#include <iostream>

std::ofstream Log::_fileStream;

// public ----------------------------------------------------------------------

Log::Log(status level) : _level(level) {}

Log::~Log() { log(_level, _ss.str()); }

void Log::setLogFile(const std::string &filename) {
  if (_fileStream.is_open())
    _fileStream.close();
  _fileStream.open(filename.c_str(), std::ios::app);
  if (!_fileStream.is_open())
    throw std::runtime_error("Could not open log file");
}

// private ---------------------------------------------------------------------

void Log::log(status level, const std::string &msg) {
  std::string label;
  std::string color;

  switch (level) {
  case DEBUG:
    label = "[DEBUG] ";
    color = CYAN;
    std::cout << color << label << msg << RESET << std::endl;
    break;
  case INFO:
    label = "[INFO] ";
    color = GREEN;
    std::cout << color << label << msg << RESET << std::endl;
    break;
  case ERROR:
    label = "[ERROR] ";
    color = RED;
    std::cerr << color << label << msg << RESET << std::endl;
    break;
  }

  if (_fileStream.is_open()) {
    _fileStream << label << msg << std::endl;
  }
}
