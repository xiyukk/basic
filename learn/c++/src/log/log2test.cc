#include "../include/log2.h"

#if 0
int main() {
  Logger logger("App", LogLevel::INFO);
  logger.debug("Debug message");
  logger.info("Info message");
  logger.warn("Warning message");
  logger.error("Error message");
  logger.fatal("Fatal message");
  int a = 10;
  while (--a)
  {
    logger.info("a = %d",a);
  }
  
}
#endif