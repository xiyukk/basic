#include <iostream>  
#include <thread>     
#include <future>    
#include <functional>
#include <queue>

// 任务队列类  
class TaskQueue {
private:
    std::queue<int> tasks;            // 任务队列
    std::mutex mutex;                 // 互斥锁
    std::condition_variable condition;// 条件变量 

public:
    // 添加任务到队列
    void addTask(int task) {
        {
            std::lock_guard<std::mutex> lock(mutex);  // 加锁
            tasks.push(task);                        // 添加任务到队列
        }
        condition.notify_all();                     // 通知所有等待线程
    }  

    // 从队列中获取任务
    int getTask() {
        std::unique_lock<std::mutex> lock(mutex);  

        while (tasks.empty()) {                     // 如果队列为空,等待 
            condition.wait(lock);
        }

        int task = tasks.front();                  // 获取队首任务
        tasks.pop();                               // 移除队首任务
        return task;
    }
};

// 线程池类
class ThreadPool {
public:
    ThreadPool(size_t n): pool(n) {}      // 构造函数,创建n个线程

    // 向线程池提交任务并获取返回值 
    template<class F, class... Args> 
    auto submit(F&& f, Args&&... args)      
    -> std::future<typename std::result_of<F(Args...)>::type> {
        
        // 创建任务包装器,用于获取返回值          
        auto task = std::make_shared<std::packaged_task<decltype(f(args...))()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );  

        // 获取任务的返回值future          
        auto res = task->get_future();    

        // 提交任务到线程池          
        pool.emplace_back([task](){ (*task)(); });    

        // 返回future          
        return res;        
    }

private:
    // 线程池的线程容器       
    std::vector<std::thread> pool;     
};

// 消费者线程函数
void consumerFunc(TaskQueue& taskQueue) {
    while (true) {
        int task = taskQueue.getTask();   // 获取任务
        std::cout << "Task: " << task << " completed!" << std::endl;
    } 
}

int main() {
    TaskQueue taskQueue;                 // 任务队列
    ThreadPool pool(4);                  // 线程池,4个线程

    // 提交10个任务到线程池并获取future
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 10; ++i) {
        futures.push_back(pool.submit(consumerFunc, std::ref(taskQueue))); 
    }

    // 提交任务到任务队列
    for (int i = 0; i < 10; ++i) {
        taskQueue.addTask(i);
    }

    // 获取future的结果,获得任务执行结果      
    for (auto& f: futures) f.get();  
}