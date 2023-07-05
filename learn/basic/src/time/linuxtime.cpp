// Test code
#include <thread>
#include "../../include/linuxtime.h"
int main() {
    {
        Timer timer;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    Timer timer;
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    timer.end();
}