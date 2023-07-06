#include <iostream>
#include <thread>
#include <chrono>  // 用于时间测量
#include <fstream> // 用于文件操作
#include <vector>
#include <iomanip> // 用于控制输出格式
#include <cstring> // 用于字符串操作

using namespace std;
using namespace chrono;

// 定义一个结构体用于存储多线程执行的结果
struct ThreadResult
{
    int thread_id;       // 线程ID
    double elapsed_time; // 执行时间（单位：秒）
};

// 定义一个函数用于测量线程的执行时间
void run_thread(int thread_id, int num_threads)
{
    auto start_time = high_resolution_clock::now(); // 记录开始时间

    // TODO: 在这里编写多线程任务的代码
    for (int i = 0; i < 100000000; i++)
    {
        int x = i * i;
    }

    auto end_time = high_resolution_clock::now();             // 记录结束时间
    duration<double> elapsed_seconds = end_time - start_time; // 计算耗时
    cout << "Thread " << thread_id << " elapsed time: " << elapsed_seconds.count() << " seconds" << endl;

    // 将执行结果保存到结构体中
    ThreadResult result = {thread_id, elapsed_seconds.count()};
    // 将结果写入文件
    ofstream outfile("thread_results.txt", ios_base::app);
    outfile << result.thread_id << "\t" << result.elapsed_time << endl;
}

int main()
{
    int num_threads = 8;    // 定义线程数
    vector<thread> threads; // 定义线程容器
    for (int i = 0; i < num_threads; i++)
    {
        threads.push_back(thread(run_thread, i, num_threads)); // 创建线程并放入容器中
    }

    // 等待所有线程结束
    for (auto &t : threads)
    {
        t.join();
    }

    // 读取执行结果文件
    ifstream infile("thread_results.txt");
    double total_elapsed_time = 0.0;
    double elapsed_time;
    int thread_id;
    while (infile >> thread_id >> elapsed_time)
    {
        total_elapsed_time += elapsed_time;
        cout << "Thread " << thread_id << " elapsed time: " << elapsed_time << " seconds" << endl;
    }
    cout << "Total elapsed time: " << total_elapsed_time << " seconds" << endl;

    // 获取CPU利用率
    string cmd = "mpstat -P ALL 1 1 | tail -n +4 | awk '{print $3\"\\t\"$NF}'";
    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe)
    {
        cerr << "Error: popen failed." << endl;
        return 1;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), pipe))
    {
        cout << buffer;
    }
    pclose(pipe);


    return 0;
}
