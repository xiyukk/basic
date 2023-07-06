#include "/home/tian/basic/learn/common/c/include/callback.h"
// 测试程序
int main()
{
    std::cout <<"xuyuli"<<std::endl;
    const int num_threads = 20;
    std::vector<std::thread> threads;

    // 创建一个CallbackManager对象
    CallbackManager manager;

    // 启动多个线程，每个线程都注册并执行回调函数
    for (int i = 0; i < num_threads; ++i)
    {
        threads.push_back(std::thread([&manager, i] {
            // 定义一个回调函数
            auto callback = [i](int value) {
                if(i==value){
                    std::cout << "true" << std::endl;
                }else{
                std::cout << "" << i << " = " << value << std::endl;
                }
            };

            manager.registerCallback(i, callback); // 注册回调函数
            manager.executeCallback(i, i);         // 执行回调函数
        }));
    }

    // 等待所有线程完成
    for (auto &thread : threads)
    {
        thread.join();
    }

    return 0;
}