#include "../include/log3.h"
// Usage:
int main()
{
    Logger logger("LINUX", LogLevel::INFO);
    int a = 10;
    int b = 9;
    for (int i = 0; i < a; i++)
    {
        logger.info("a =", i,"dahdk",10,"daldj");
        for (b; b >= 0; b--)
        {
            logger.info("b =", b);
        }
    }
    return 0;
}