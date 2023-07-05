#include <stdio.h>
#include <unistd.h>
#include "threadpool.h"

// 任务函数示例
void print_hello(void *arg) {
    int id = *((int *)arg);
    printf("Hello from task %d\n", id);
}

int main() {
    // 创建一个包含4个线程的线程池
    threadpool_t *pool = threadpool_create(4);

    // 添加10个任务到线程池
    int task_ids[10];
    for (int i = 0; i < 10; i++) {
        task_ids[i] = i;
        threadpool_add_task(pool, print_hello, (void *)&task_ids[i]);
    }

    // 等待任务完成
    sleep(5);

    // 销毁线程池
    threadpool_destroy(pool);

    return 0;
}