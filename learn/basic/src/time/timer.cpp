#include "../../include/timer.h"
#include <thread>

void doSomething() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main() {
    {
        Timer timer;  // 方式一:构造函数启动,析构函数结束
        doSomething();
    }

    {
        Timer timer;
        timer.start();  // 方式二:手动启动
        doSomething();
        timer.end();   // 手动结束
    }

    // 测试循环
    for (int i = 0; i < 10; i++) { 
        Timer timer;
        doSomething();
    }

    // 测试线程
    std::thread t1([](){
        Timer timer;
        doSomething();
    });
    t1.join();

    std::thread t2([](){
         Timer timer;
         timer.start();
         doSomething();
         timer.end();
    });
    t2.join();
}