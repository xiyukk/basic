#include <iostream>
#include <ctime>
#include <chrono>
#include <cmath>
#include <locale>
#include <ratio>

using namespace std;

void testfunc(double max)
{
    double sum = 0;
    for (int i = 0; i < max; i++)
    {
        sum += sqrt(i);
    }
    cout << "sum = " << sum << endl;
}

int main()
{
    /*
     * 获取当前时间
     */
    // 实现1
    // time_t now = time(nullptr);
    // cout << "now is: " << ctime(&now) << endl;

    // // 实现2
    // auto nows = chrono::system_clock::now();
    // time_t time = chrono::system_clock::to_time_t(nows);
    // cout << "chrono time is: " << ctime(&time) << endl;

    /*
     * 计算时间差
     */
    // 实现1：单位为s
    /* time_t time1 = time(nullptr);
    testfunc(1000);
    time_t time2 = time(nullptr);
    double time_diff = difftime(time2, time1);
    cout << "time1: " << time1 << endl;
    cout << "time2: " << time2 << endl;
    cout << "time_diff: " << time_diff << "s" << endl;

    // 实现2
    auto start = chrono::steady_clock::now();
    testfunc(1000);
    auto end = chrono::steady_clock::now();
    auto time_diffs = end - start;
    auto duration = chrono::duration_cast<chrono::nanoseconds>(time_diffs);
    cout << "Operation cost : " << duration.count() << "ns" << endl;
    auto durations = chrono::duration_cast<chrono::milliseconds>(time_diffs);
    cout << "Operations cost : " << durations.count() << "ms" << endl; */

    /* time_t now = time(nullptr);

    // 使用gmtime将std::time_t的纪元时间转换为UTC时间
    tm *gm_time = gmtime(&now);
    // 使用localtime将纪元时间转换为本地时区所代表的日历时间
    tm *local_time = localtime(&now);

    tm * t = localtime(&now);

    cout << "gmtime: " << asctime(gm_time);
    // 拆分tm结构体的字段
    cout << "Now is: " << t->tm_year + 1900 << "/" << t->tm_mon + 1<< "/" << t->tm_mday << " ";    cout << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl;
    cout << "local_time: " << asctime(local_time);
    cout << "Now is: " << ctime(&now); */

    // c++17引进timespec，含纳秒
    /* timespec ts;
    timespec_get(&ts, TIME_UTC);
    char buff[100];
    strftime(buff, sizeof buff, "%D %T", std::gmtime(&ts.tv_sec));
    printf("Current time: %s.%09ld UTC\n", buff, ts.tv_nsec); */

    //-------------------------------------------------------------------------------

    /*
     * chrono库
     */

    ratio_add<ratio<5, 7>, ratio<59, 1023>> result;
    double value = ((double)result.num) / result.den;
    cout << result.num << " / " << result.den << " = " << value << endl;

    // 以s为基准，ms为1/1000，依次类推
    // std::ratio<1, 1000> milliseconds;
    // std::ratio<1, 1000000> microseconds;
    // std::ratio<1, 1000000000> nanoseconds;

    // c++11
    // chrono::hours two_hours(2);
    // chrono::minutes five_minutes(5);

    // c++14
    //  using namespace std::chrono_literals;
    //  auto two_hours = 2h;
    //  auto five_minutes = 5min;

    // auto duration = two_hours + five_minutes;
    // auto seconds = chrono::duration_cast<chrono::seconds>(duration);
    // cout << "02:05 is " << seconds.count() << " seconds" << endl;

    auto start = chrono::steady_clock::now();
    
    testfunc(100000000);
    auto end = chrono::steady_clock::now();

    auto time_diff = end - start;
    auto duration = chrono::duration_cast<chrono::milliseconds>(time_diff);
    cout << "Operation cost : " << duration.count() << "ms" << endl;

    return 0;
}