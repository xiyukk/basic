#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <tuple>
#include <utility>

// 日志级别枚举
enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

// 日志类
class Logger {
public:
    // 构造函数
    Logger(const std::string& log_file, LogLevel level = LogLevel::INFO)
        : log_level_(level), log_file_(log_file) {
        // 打开日志文件
        log_stream_.open(log_file_, std::ios::app);
    }

    // 析构函数
    ~Logger() {
        // 关闭日志文件
        log_stream_.close();
    }

    // 日志输出函数
    template<typename... Args>
    void log(LogLevel level, const std::string& format, Args... args) {
        if (level >= log_level_) {
            // 获取当前时间
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);

            // 格式化时间
            std::ostringstream time_stream;
            time_stream << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

            // 格式化日志消息
            std::string msg = format_message(format, std::make_tuple(args...));

            // 输出日志
            log_stream_ << "[" << time_stream.str() << "] "
                        << log_level_str(level) << ": "
                        << msg << std::endl;
        }
    }

private:
    // 日志级别转换为字符串
    std::string log_level_str(LogLevel level) {
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
                return "UNKNOWN";
        }
    }

    // 格式化日志消息
    template<typename... Args>
    std::string format_message(const std::string& format, const std::tuple<Args...>& args) {
        std::ostringstream msg_stream;
        format_message_impl(msg_stream, format, 0, args, std::make_index_sequence<sizeof...(Args)>());
        return msg_stream.str();
    }

    template<typename Tuple, size_t... Is>
    void format_message_impl(std::ostringstream& stream, const std::string& format, size_t i, const Tuple& args, std::index_sequence<Is...>) {
        if (i < format.size()) {
            if (format[i] == '%' && i + 1 < format.size() && format[i + 1] == 'v') {
                // stream << std::get<Is>(args);
                (stream << ... << std::get<Is>(args));
                format_message_impl(stream, format, i + 2, args, std::make_index_sequence<sizeof...(Is) - 1>());
            } else {
                stream << format[i];
                format_message_impl(stream, format, i + 1, args, std::make_index_sequence<sizeof...(Is)>());
            }
        }
    }

    // 递归终止函数
    template<typename Tuple>
    void format_message_impl(std::ostringstream& stream, const std::string& format, size_t i, const Tuple& args, std::index_sequence<>) {
        if (i < format.size()) {
            stream << format[i];
            format_message_impl(stream, format, i + 1, args, std::make_index_sequence<0>());
        }
    }

    LogLevel log_level_;
    std::string log_file_;
    std::ofstream log_stream_;
};


