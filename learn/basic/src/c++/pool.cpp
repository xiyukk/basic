#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>

class ThreadPool
{
public:
    // 构造函数，初始化线程池
    ThreadPool(size_t num_threads)
    {
        // 创建工作线程
        for (size_t i = 0; i < num_threads; ++i)
        {
            workers.emplace_back([this] {
                while (true)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });

                        if (this->stop && this->tasks.empty())
                        {
                            return;
                        }

                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    task();
                }
            });
        }
    }

    // 添加任务到线程池
    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>
    {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<return_type> res = task->get_future();

        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            if (stop)
            {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            tasks.emplace([task]() { (*task)(); });
        }

        condition.notify_one();
        return res;
    }

    // 析构函数，等待任务完成并销毁线程池
    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }

        condition.notify_all();

        for (std::thread& worker : workers)
        {
            worker.join();
        }
    }

private:
    std::vector<std::thread> workers;          // 工作线程
    std::queue<std::function<void()>> tasks;   // 任务队列
    std::mutex queue_mutex;                    // 任务队列互斥锁
    std::condition_variable condition;         // 用于通知线程有新任务的条件变量
    bool stop = false;                         // 线程池停止标志
};

int main()
{
    ThreadPool thread_pool(4); // 创建一个包含4个线程的线程池

    // 提交一些任务到线程池
    std::vector<std::future<int>> results;
    for (int i = 0; i < 8; ++i)
    {
        results.emplace_back(thread_pool.enqueue([](int task_id) {
            std::cout << "Task " << task_id << " is running on thread " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return task_id * task_id;
        }, i));
    }

    // 获取任务的结果
    for (auto& result : results)
    {
        std::cout << "Result: " << result.get() << std::endl;
    }

    return 0;
}