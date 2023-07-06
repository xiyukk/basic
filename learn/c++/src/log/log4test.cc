#include "../../include/log4.h"
int main() {
    Logger logger("log4.txt", LogLevel::DEBUG);

    logger.log(LogLevel::DEBUG, "%v,%v", "debug", 42);
    logger.log(LogLevel::INFO, "This is an %v message", "info");
    logger.log(LogLevel::WARNING, "This is a %v message", "warning");
    logger.log(LogLevel::ERROR, "This is an %v message", "error");

    return 0;
}