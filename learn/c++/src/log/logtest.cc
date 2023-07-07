#include "../include/log.h"
int main() {
    Logger logger(LogLevel::DEBUG);

    logger.Debug("Debug message");
    logger.Info("Info message");
    logger.Warning("Warning message");
    logger.Error("Error message");
    logger.Info("xiyuli");

    return 0;
}
