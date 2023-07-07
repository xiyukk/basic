#include <iostream>
#include <future>
#include <thread>
#include <chrono>

/* 
在这个示例中，我们首先使用std::packaged_task执行异步操作。我们将square函数包装为std::packaged_task对象，并
将该对象传递给一个新线程。std::future对象用于获取异步操作的结果。

接下来，我们使用std::promise进行异步操作。我们创建一个std::promise对象，并将其传递给一个新线程。在新线程中，
我们设置std::promise的值。std::future对象用于获取设置的值。

最后，我们使用std::async启动异步任务。std::async启动异步任务，并返回一个std::future对象，该对象用于获取异步操作的结果。
 */


// 一个简单的函数，用于计算平方
int square(int n) {
    return n * n;
}

int main() {
    // 使用std::packaged_task
    std::packaged_task<int(int)> task(square); // 将square函数包装为packaged_task
    std::future<int> future1 = task.get_future(); // 获取与task关联的future对象
    std::thread thread1(std::move(task), 5); // 将task传递给新线程
    std::cout << "Square of 5: " << future1.get() << std::endl; // 获取异步操作的结果
    thread1.join();

    // 使用std::promise
    std::promise<int> promise;
    std::future<int> future2 = promise.get_future(); // 获取与promise关联的future对象
    std::thread thread2([](std::promise<int>& p) {
        p.set_value(square(6)); // 在新线程中设置promise的值
    }, std::ref(promise));
    std::cout << "Square of 6: " << future2.get() << std::endl; // 获取异步操作的结果
    thread2.join();

    // 使用std::async
    std::future<int> future3 = std::async(std::launch::async, square, 7); // 使用std::async启动异步任务
    std::cout << "Square of 7: " << future3.get() << std::endl; // 获取异步操作的结果

    return 0;
}