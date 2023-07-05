#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

// 任务队列类
class TaskQueue {
private:
    std::queue<int> tasks;             // 存储任务的队列
    std::mutex mutex;                  // 互斥锁，保证线程安全
    std::condition_variable condition; // 条件变量，用于任务的等待和通知

public:
    // 添加任务到队列
    void addTask(int task) {
        {
            std::lock_guard<std::mutex> lock(mutex);  
            tasks.push(task);                      
        }
        condition.notify_all();                   
    }

    // 从队列中获取任务
    int getTask() {
        std::unique_lock<std::mutex> lock(mutex); // 加锁，保证线程安全

        // 使用while循环等待，避免虚假唤醒
        while (tasks.empty()) {
            condition.wait(lock); // 阻塞当前线程，等待任务的到来
        }

        int task = tasks.front(); // 获取队列中的任务
        tasks.pop();              // 移除已获取的任务
        return task;              // 返回任务
    }
};

// 消费者线程函数
void consumerFunc(TaskQueue& taskQueue) {
    while (true) {
        int task = taskQueue.getTask(); // 从任务队列中获取任务
        std::cout << "Task: " << task << " is being processed by thread: " << std::this_thread::get_id() << std::endl;
        // 执行任务的具体操作
        // ...

        // 模拟任务处理时间
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    TaskQueue taskQueue;

    // 创建多个消费者线程
    std::thread consumerThread1(consumerFunc, std::ref(taskQueue));
    std::thread consumerThread2(consumerFunc, std::ref(taskQueue));

    // 添加一些任务到任务队列
    for (int i = 0; i < 100; ++i) {
        taskQueue.addTask(i);
    }

    // 主线程等待消费者线程结束
    consumerThread1.join();
    consumerThread2.join();

    return 0;
}