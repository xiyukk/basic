// #pragma once
#include <sys/time.h>
#include <chrono>
#include <ctime>
#include <fstream>
#include <thread>
#include <iostream>
#include <string>

#define CAL_SCOPE_TIME(x) wzq::timer::TimerLog t(x)

using llong = long long;
using namespace std::chrono;
using std::cout;
using std::endl;
namespace wzq
{

    namespace timer
    {

        class TimerLog
        {
        public:
            TimerLog(const std::string tag)
            { // 对象构造时候保存开始时间
                m_begin_ = high_resolution_clock::now();
                m_tag_ = tag;
            }
            void Reset() { m_begin_ = high_resolution_clock::now(); }
            llong Elapsed()
            {
                return static_cast<llong>(
                    duration_cast<std::chrono::milliseconds>(high_resolution_clock::now() - m_begin_).count());
            }
            ~TimerLog()
            { // 对象析构时候计算当前时间与对象构造时候的时间差就是对象存活的时间
                auto time =
                    duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_begin_).count();
                std::cout << "time { " << m_tag_ << " } " << static_cast<double>(time) << " ms" << std::endl;
            }

        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> m_begin_;
            std::string m_tag_;
        };
    } // namespace timer
} // namespace wzq

void TestTimerLog()
    {
        auto func = []()
        {
            for (int i = 0; i < 5; ++i)
            {
                cout << "i " << i << endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        };
        {
            CAL_SCOPE_TIME("func time");
            func();
        }
    }

int main()
{
    void TestTimerLog();
}
