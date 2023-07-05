#include "../../include/timer.h"
#include <thread>
#include <vector>

// 线程任务函数
void doSomething() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
}

int main() {
    // 定义8个线程
    std::vector<std::thread> threads;
    for (int i = 0; i < 8; i++) {
        threads.push_back(std::thread(doSomething));
    }

    // 统计每个线程的运行时间
    std::vector<double> durations;  // 运行时间列表
    for (auto& thread : threads) {
        Timer timer;  // 构造函数启动计时
        thread.join();  // 等待线程结束
        auto duration = timer.duration_.count();  // 获取运行时间
        durations.push_back(duration);  // 添加到列表
    }

    // 输出每个线程的运行时间(ms)
    for (int i = 0; i < threads.size(); i++) {
        std::cout << "Thread " << i + 1 << ": " << durations[i] / 1000000.0 
                  << "ms" << std::endl;
    }
}