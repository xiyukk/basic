#include <iostream>
#include <chrono>
#include <string>
#include <queue>
#define NS_MS 1000000

class Timer {
public:
    Timer() {
        start_ = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        end_ = std::chrono::high_resolution_clock::now();
        duration_ = std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_);
        std::cout << duration_.count() << "ms" << std::endl;
    }

    void start() {
        start_ = std::chrono::high_resolution_clock::now();
    }

    void end() {
        end_ = std::chrono::high_resolution_clock::now();
        duration_ = std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_);
        std::cout << duration_.count() << "ms" << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_;
public:
    std::chrono::milliseconds duration_;
};

#if 0
int main() {
    {
        Timer timer;  // 进入作用域启动计时,退出作用域输出结果
    }

    Timer timer;
    timer.start();   // 手动启动计时
    doSomething();
    timer.end();     // 手动结束计时并输出结果
}
#endif