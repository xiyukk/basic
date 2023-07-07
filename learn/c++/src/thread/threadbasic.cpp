#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx; // 互斥锁，用于在多线程中保护共享资源

// 定义一个简单的线程函数，接收一个参数表示线程ID
void thread_function(int thread_id) {
    std::unique_lock<std::mutex> lock(mtx); // 使用互斥锁保护共享资源
    std::cout << "Thread ID: " << thread_id << " is running." << std::endl;
    lock.unlock();

    // 模拟线程执行需要一定时间
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    const int num_threads = 5; // 线程数量
    std::vector<std::thread> threads; // 定义一个std::vector容器来保存线程对象

    // 创建线程并将它们保存到容器中
    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread(thread_function, i));
        std::cout << "thread " << i << " id is " <<threads[i].get_id() << std::endl; 
    }

    

    // 等待所有线程完成执行
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    std::cout << "CPU core nums is = " << std::thread::hardware_concurrency() << std::endl;
    std::cout << "All threads have finished." << std::endl;

    return 0;
}