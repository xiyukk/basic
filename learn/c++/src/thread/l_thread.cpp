#if 1
#include <iostream>
#include <thread>

// 线程函数
void my_thread_function() {
    std::cout << "Hello from my_thread_function!" << std::endl;
}

int main() {
    // 创建一个线程，将 my_thread_function 作为线程函数
    std::thread my_thread(my_thread_function);

    // 等待线程完成
    my_thread.join();

    return 0;
}
#endif

#if 0
// 1. 介绍 std::mutex、std::lock_guard 和 std::unique_lock 的用法。关键是强调线程安全性和避免竞争条件。
// 以下是一个使用互斥量保护共享数据的示例：

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex mtx; // 定义互斥量
int shared_counter = 0;

// 线程函数
void increment_counter(int n) {
    for (int i = 0; i < n; ++i) {
        std::unique_lock<std::mutex> lock(mtx); // 使用 unique_lock 锁住互斥量
        ++shared_counter;
        lock.unlock(); // 解锁互斥量
    }
}

int main() {
    const int num_threads = 10;
    const int num_iterations = 1000;

    // 创建线程
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(increment_counter, num_iterations);
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final counter value: " << shared_counter << std::endl;

    return 0;
}

#endif

#if 0
// 1. 讲解 std::condition_variable 的用法，如何与互斥量结合使用以实现线程间的同步。以下是一个条件变量的示例：
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

// 线程函数
void wait_for_signal() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [](){ return ready; }); // 等待 ready 变为 true
    std::cout << "Received signal!" << std::endl;
}

int main() {
    std::thread waiting_thread(wait_for_signal);

    {
        std::unique_lock<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one(); // 发送信号

    waiting_thread.join();

    return 0;
}
#endif

#if 0
// 1. 介绍异步任务和 std::future 类的用法，以实现简洁的多线程编程。以下是一个使用 std::async 和 std::future 的示例：
#include <iostream>
#include <future>
#include <vector>

// 计算指定范围内所有整数的和
long long sum_range(int start, int end) {
    long long sum = 0;
    for (int i = start; i <= end; ++i) {
        sum += i;
    }
    return sum;
}

int main() {
    // 创建异步任务
    std::vector<std::future<long long>> futures;
    for (int i = 0; i < 10; ++i) {
        futures.push_back(std::async(sum_range, i * 1000 + 1, (i + 1) * 1000));
    }

    // 获取任务结果
    long long total_sum = 0;
    for (auto& future : futures) {
        total_sum += future.get();
    }

    std::cout << "Total sum: " << total_sum << std::endl;

    return 0;
}

#endif

#if 0
1. 介绍 std::atomic 类的用法，以实现无锁的线程安全数据结构和操作。以下是一个使用 std::atomic 的示例：
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

std::atomic<int> shared_counter(0);

// 线程函数
void increment_counter(int n) {
    for (int i = 0; i < n; ++i) {
        ++shared_counter; // 使用 atomic 变量的原子操作
    }
}

int main() {
    const int num_threads = 10;
    const int num_iterations = 1000;

    // 创建线程
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(increment_counter, num_iterations);
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final counter value: " << shared_counter.load() << std::endl;

    return 0;
}

#endif

#if 0

#endif

