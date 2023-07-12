// 以下是一个使用 std::condition_variable 实现生产者-消费者模式的示例：
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

#if 1

std::mutex mtx;
std::condition_variable cv;
std::queue<int> queue;
const int max_queue_size = 5;

// 生产者线程函数
void producer() {
    int item = 0;
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [](){ return queue.size() < max_queue_size; }); // 等待队列有空闲空间

        queue.push(item);
        std::cout << "Produced item: " << item << std::endl;
        ++item;
        lock.unlock();
        cv.notify_all(); // 通知其他线程

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 模拟生产延迟
    }
}

// 消费者线程函数
void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [](){ return !queue.empty(); }); // 等待队列非空

        int item = queue.front();
        queue.pop();
        std::cout << "Consumed item: " << item << std::endl;
        lock.unlock();
        cv.notify_all(); // 通知其他线程

        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // 模拟消费延迟
    }
}

int main() {
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    return 0;
}

#endif