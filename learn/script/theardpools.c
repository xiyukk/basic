#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 10
#define MAX_QUEUE 1000

typedef struct
{
    void (*function)(void *);
    void *argument;
} threadpool_task_t;

typedef struct
{
    pthread_mutex_t lock;               // 互斥锁
    pthread_cond_t notify;              // 条件变量
    threadpool_task_t queue[MAX_QUEUE]; // 线程池任务队列
    int queue_size;                     // 任务队列长度
    int head, tail;                     // 队列首尾指针
    int count;                          // 当前线程数
    int shutdown;                       // 是否关闭线程池
    int started;                        // 已经开始的线程数
    pthread_t thread_id[MAX_THREADS];   // 线程ID数组
} threadpool_t;

// 初始化线程池
int threadpool_init(threadpool_t *pool, int threads)
{
    // 参数检查
    if (threads < 0 || threads > MAX_THREADS)
    {
        threads = MAX_THREADS;
    }
    // 初始化各种数据结构
    pool->queue_size = 0;
    pool->head = pool->tail = pool->count = 0;
    pool->shutdown = pool->started = 0;
    // 分配线程ID数组的内存空间
    pthread_t *thread_id = (pthread_t *)malloc(sizeof(pthread_t) * threads);
    pool->thread_id = thread_id;
    // 初始化互斥锁和条件变量
    pthread_mutex_init(&(pool->lock), NULL);
    pthread_cond_init(&(pool->notify), NULL);
    // 创建指定数量的线程
    for (int i = 0; i < threads; i++)
    {
        pthread_create(&(pool->thread_id[i]), NULL, threadpool_thread, (void *)pool);
        pool->count++;
        pool->started++;
    }
    return 0;
}

// 向线程池中添加任务
int threadpool_add(threadpool_t *pool, void (*function)(void *), void *argument)
{
    int err = 0;
    int next;
    // 加锁，保证线程安全
    if (pool == NULL || function == NULL)
    {
        return -1;
    }
    pthread_mutex_lock(&(pool->lock));
    // 计算下一个插入的位置
    next = pool->tail + 1;
    next = (pool->queue_size == MAX_QUEUE) ? 0 : next;
    do
    {
        // 检查队列是否已满
        if (pool->queue_size == MAX_QUEUE)
        {
            err = -1;
            break;
        }
        // 添加任务到队列中
        pool->queue[pool->tail].function = function;
        pool->queue[pool->tail].argument = argument;
        pool->tail = next;
        pool->queue_size += 1;
        // 发送信号，通知有新的任务加入了
        if (pthread_cond_signal(&(pool->notify)) != 0)
        {
            err = -1;
            break;
        }
    } while (false);
    // 解锁
    pthread_mutex_unlock(&(pool->lock));
    return err;
}

// 销毁线程池
int threadpool_destroy(threadpool_t *pool)
{
    int i, err = 0;
    if (pool == NULL)
    {
        return -1;
    }
    // 加锁，保证线程安全
    pthread_mutex_lock(&(pool->lock));
    // 如果已经关闭了线程池，则直接返回
    if (pool->shutdown)
    {
        err = -1;
    }
    else
    {
        // 发送关闭信号
        pool->shutdown = 1;
        // 发送条件变量信号，通知所有等待的线程
        if (pthread_cond_broadcast(&(pool->notify)) != 0)
        {
            err = -1;
        }

        // 等待所有线程退出
        while (pool->count > 0)
        {
            if (pthread_cond_wait(&(pool->notify), &(pool->lock)) != 0)
            {
                err = -1;
                break;
            }
        }
        // 释放线程ID数组的内存空间
        if (pool->thread_id)
        {
            free(pool->thread_id);
        }
        // 销毁互斥锁和条件变量
        pthread_mutex_destroy(&(pool->lock));
        pthread_cond_destroy(&(pool->notify));
    }
    // 解锁
    pthread_mutex_unlock(&(pool->lock));
    return err;
}

// 线程池中线程的执行函数
void *threadpool_thread(void *threadpool)
{
    threadpool_t *pool = (threadpool_t)threadpool;
    threadpool_task_t task;
    while (true)
    {
        // 加锁，保证线程安全
        pthread_mutex_lock(&(pool->lock));
        // 队列为空且没有收到关闭信号，则等待
        while (pool->queue_size == 0 && !pool->shutdown)
        {
            pthread_cond_wait(&(pool->notify), &(pool->lock));
        }
        // 收到关闭信号则退出循环
        if (pool->shutdown)
        {
            break;
        }
        // 获取队列头部任务
        task.function = pool->queue[pool->head].function;
        task.argument = pool->queue[pool->head].argument;
        // 更新队列状态
        pool->head += 1;
        pool->head = (pool->head == MAX_QUEUE) ? 0 : pool->head;
        pool->queue_size -= 1;
        // 解锁
        pthread_mutex_unlock(&(pool->lock));
        // 执行任务
        ((void()(void *))(task.function))(task.argument);
    }
    // 更新线程池状态
    pthread_mutex_lock(&(pool->lock));
    pool->count--;
    pthread_mutex_unlock(&(pool->lock));
    pthread_exit(NULL);
}

// 测试任务函数
void print_hello(void *arg)
{
    printf("Hello from thread %d\n", *((int *)arg));
    free(arg);
}

// 主函数
int main()
{
    threadpool_t pool;
    int args[10];
    // 初始化线程池
    threadpool_init(&pool, 5);
    // 添加任务到队列中
    for (int i = 0; i < 10; i++)
    {
        int *arg = (int *)malloc(sizeof(int));
        *arg = i;
        threadpool_add(&pool, print_hello, (void *)arg);
        sleep(1);
    }
    // 销毁线程池
    threadpool_destroy(&pool);
    return 0;
}