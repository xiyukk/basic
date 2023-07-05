#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>

// 任务结构体
typedef struct task {
    void (*function)(void *arg); // 任务函数
    void *arg;                   // 任务函数参数
    struct task *next;           // 指向下一个任务的指针
} task_t;

// 线程池结构体
typedef struct threadpool {
    pthread_mutex_t lock;        // 互斥锁
    pthread_cond_t cond;         // 条件变量
    pthread_t *threads;          // 线程数组
    task_t *task_queue_head;     // 任务队列头指针
    int thread_count;            // 线程数量
    int task_queue_size;         // 任务队列大小
    int shutdown;                // 关闭标志
} threadpool_t;

// 函数声明
threadpool_t *threadpool_create(int thread_count);
void threadpool_add_task(threadpool_t *pool, void (*function)(void *), void *arg);
void threadpool_destroy(threadpool_t *pool);

#endif // THREADPOOL_H