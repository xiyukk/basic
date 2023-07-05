#include <string>
#include <fstream>
#include <iostream> 
#include <sstream>
#include <ctime>
#include <chrono>

// 日志库以此版本为准

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
  
  template<typename... Args>
  void debug(std::string msg, Args... args) {
    log(LogLevel::DEBUG, msg, args...);
  }
  
  template<typename... Args> 
  void info(std::string msg, Args... args) {
    log(LogLevel::INFO, msg, args...);
  }
  
  template<typename... Args>
  void warn(std::string msg, Args... args) {
    log(LogLevel::WARNING, msg, args...);
  }
  
  template<typename... Args>
  void error(std::string msg, Args... args) {
    log(LogLevel::ERROR, msg, args...);
  }
  
  template<typename... Args>
  void fatal(std::string msg, Args... args) {
    log(LogLevel::FATAL, msg, args...);
  }
  
private:
  std::string name;
  LogLevel level;
  
  template<typename... Args>
  void log(LogLevel lvl, std::string msg, Args... args) {
    if (lvl >= level) {
      std::stringstream ss;
      ss << getCurrentTime() << " [" << name << "] [" 
         << getLevelString(lvl) << "] " << msg;
      printArgs(ss, args...);
      ss << std::endl;
      std::cout << ss.str();
      
      std::ofstream file("log3.txt", std::ios_base::app);
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
  
  template<typename T>
  void printArgs(std::stringstream &ss, T arg) {
    ss << " " << arg;
  }
  
  template<typename T, typename... Args>
  void printArgs(std::stringstream &ss, T arg, Args... args) {
    ss << " " << arg;
    printArgs(ss, args...);
  }
};

