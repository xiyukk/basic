#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>


enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    Logger(LogLevel logLevel) : m_LogLevel(logLevel) {}

    template<typename... Args>
    void Debug(Args&&... args) {
        Log(LogLevel::DEBUG, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Info(Args&&... args) {
        Log(LogLevel::INFO, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Warning(Args&&... args) {
        Log(LogLevel::WARNING, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Error(Args&&... args) {
        Log(LogLevel::ERROR, std::forward<Args>(args)...);
    }

private:
    template<typename... Args>
    void Log(LogLevel level, Args&&... args) {
        if (level >= m_LogLevel) {
            std::stringstream ss;
            ss << "[" << GetTimestamp() << "] [" << ToString(level) << "] ";
            Print(ss, std::forward<Args>(args)...);
            std::cout << ss.str() << std::endl;
        }
    }

    std::string GetTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t_now), "%Y-%m-%d %X");
        return ss.str();
    }

    template<typename T>
    void Print(std::ostream& os, const T& t) {
        os << t;
    }

    template<typename T, typename... Args>
    void Print(std::ostream& os, const T& t, Args&&... args) {
        os << t;
        Print(os, std::forward<Args>(args)...);
    }

    std::string ToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG:
                return "DEBUG";
            case LogLevel::INFO:
                return "INFO";
            case LogLevel::WARNING:
                return "WARNING";
            case LogLevel::ERROR:
                return "ERROR";
            default:
                return "";
        }
    }

private:
    LogLevel m_LogLevel;
};
