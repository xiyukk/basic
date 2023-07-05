#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定义线程结构体
typedef struct {
    void (*task)(void *arg);   // 任务函数指针
    void *arg;                 // 任务参数
} thread_t;

// 定义线程数组和计数器
thread_t threads[10];          // 最多支持10个线程同时运行
int num_threads = 0;           // 当前线程数

// 线程执行函数
void *thread_func(void *arg) {
    thread_t *thread = (thread_t *)arg;
    thread->task(thread->arg);  // 执行任务函数
    return NULL;
}

// 创建新线程
int create_thread(void (*task)(void *), void *arg) {
    if (num_threads == 10) {   // 已经达到最大线程数
        return -1;
    }
    thread_t *thread = &threads[num_threads++];
    thread->task = task;
    thread->arg = arg;
    return 0;
}

// 主函数
int main() {
    srand(time(NULL));        // 初始化随机种子

    // 单线程执行任务
    clock_t start = clock();   // 记录开始时间
    for (int i = 0; i < 10; i++) {
        int arg = rand() % 100; // 随机生成参数
        printf("Task %d: arg=%d\n", i, arg);
        // 执行任务函数
        void task(void *arg) {
            int sleep_time = *(int *)arg;
            printf("Task %d start\n", i);
            delay(sleep_time);   // 模拟任务执行时间
            printf("Task %d end\n", i);
        }
        task(&arg);
    }
    clock_t end = clock();     // 记录结束时间
    printf("Single thread time: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    // 多线程执行任务
    num_threads = 0;           // 重置线程计数器
    start = clock();           // 记录开始时间
    for (int i = 0; i < 10; i++) {
        int arg = rand() % 100; // 随机生成参数
        printf("Task %d: arg=%d\n", i, arg);
        create_thread(task, &arg); // 创建新线程并执行任务函数
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i].thread_id, NULL); // 等待所有线程执行完成
    }
    end = clock();             // 记录结束时间
    printf("Multi-thread time: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    return 0;
}
