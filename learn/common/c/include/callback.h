#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <mutex>
#include <shared_mutex>
#include <map>
using namespace std;
// 定义一个表示回调函数的类型别名
using Callback = std::function<void(int)>;

class CallbackManager
{
private:
    std::map<int, Callback> callbacks_; // 存储回调函数的容器
    std::shared_mutex mutex_;           // 保护回调函数容器的共享互斥锁

public:
    // 注册回调函数
    void registerCallback(int id, Callback callback)
    {
        std::unique_lock lock(mutex_);      // 使用std::unique_lock对互斥锁进行加锁
        callbacks_[id] = std::move(callback); // 将回调函数添加到容器中
    }

    // 执行回调函数
    void executeCallback(int id, int value)
    {
        std::shared_lock lock(mutex_); // 使用std::shared_lock对互斥锁进行加锁

        // 检查对应ID的回调函数是否存在
        auto it = callbacks_.find(id);
        if (it != callbacks_.end())
        {
            // 如果找到了回调函数，执行它
            it->second(value);
        }
    }
};

