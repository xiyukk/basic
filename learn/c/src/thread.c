#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

void *task1(void *arg)
{
    // 执行任务1的代码
    printf("task1 runing...\n");
    sleep(2);
}

void *task2(void *arg)
{
    // 执行任务2的代码
    printf("task2 runing...\n");
    sleep(2);
}


/* 

在main函数中，我们需要创建两个线程，分别执行task1和task2函数。具体步骤如下：

定义两个pthread_t类型的变量thread1和thread2，用于存储线程ID。

调用pthread_create函数，创建线程。该函数的参数依次为：线程ID、线程属性（通常为NULL）、线程函数、线程函数的参数。

调用pthread_join函数，等待线程结束。该函数的参数为线程ID。

 */

/* 

为了测试多线程和单线程实际运行所花费的时间，我们可以使用clock函数。该函数返回程序从启动到当前时刻所经过的CPU时钟周期数。具体步骤如下：

在main函数开始处调用clock函数，并将其结果赋值给一个变量start_time。

在所有线程结束后，再次调用clock函数，并将其结果减去start_time，得到程序运行的CPU时钟周期数。

将CPU时钟周期数除以CLOCKS_PER_SEC（常量，表示每秒的CPU时钟周期数），即可得到程序运行的时间（单位为秒）。

 */

int main()
{
    pthread_t thread1, thread2;

    clock_t start_time, end_time;
    double elapsed_time;

    start_time = clock();

    // 创建线程1
    if(pthread_create(&thread1, NULL, task1, NULL) != 0)
    {
        printf("Error creating thread1\n");
        return -1;
    }

    // 创建线程2
    if(pthread_create(&thread2, NULL, task2, NULL) != 0)
    {
        printf("Error creating thread2\n");
        return -1;
    }

    // 等待线程1结束
    if(pthread_join(thread1, NULL) != 0)
    {
        printf("Error joining thread1\n");
        return -1;
    }

    // 等待线程2结束
    if(pthread_join(thread2, NULL) != 0)
    {
        printf("Error joining thread2\n");
        return -1;
    }

    end_time = clock();
    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC *1000 ;

    printf("Time elapsed: %.3f ms\n", elapsed_time);

    return 0;
}

