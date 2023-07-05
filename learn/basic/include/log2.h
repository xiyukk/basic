#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <chrono>

#if 0
enum class LogLevel {
  DEBUG, 
  INFO, 
  WARNING, 
  ERROR, 
  FATAL
};

class Logger {
public:
  Logger(std::string name, LogLevel level) 
    : name(name), level(level) {}
  
  void debug(std::string msg) {
    log(LogLevel::DEBUG, msg);
  }
  
  void info(std::string msg) {
    log(LogLevel::INFO, msg);
  }
  
  void warn(std::string msg) {
    log(LogLevel::WARNING, msg);
  }
  
  void error(std::string msg) {
    log(LogLevel::ERROR, msg);
  }
  
  void fatal(std::string msg) {
    log(LogLevel::FATAL, msg);
  }
  
private:
  std::string name;
  LogLevel level;
  
  void log(LogLevel lvl, std::string msg) {
    if (lvl >= level) {
      std::stringstream ss;
      ss << getCurrentTime() << " [" << name << "] [" 
         << getLevelString(lvl) << "] " << msg << std::endl;
      std::cout << ss.str();
      
      std::ofstream file("log.txt", std::ios_base::app);
      file << ss.str();
      file.close();
    }
  }
  
  std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::string ts = std::ctime(&in_time_t);
    ts.resize(ts.size()-1); // remove trailing \n
    return ts;
  }
  
  std::string getLevelString(LogLevel lvl) {
    switch (lvl) {
      case LogLevel::DEBUG: return "DEBUG";
      case LogLevel::INFO: return "INFO"; 
      case LogLevel::WARNING: return "WARNING";
      case LogLevel::ERROR: return "ERROR";
      case LogLevel::FATAL: return "FATAL";
    }
  }
};

#endif