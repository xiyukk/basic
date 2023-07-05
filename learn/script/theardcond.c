/*

在这个增强版的程序中，我们为每个生产者线程分配了缓冲区的一部分空间，
这样可以保证所有生产者线程互不干扰。同时，我们将缓冲区是否已满和是否为空的标志变量改为了布尔类型，
并在程序中加入了更多的条件判断语句来避免死锁等问题的发生。具体来说，当消费者线程取出数据后，
如果缓冲区非空就广播信号唤醒其他等待的消费者线程；如果缓冲区为空并且所有生产者线程都已经结束，则退出循环。
而当生产者线程生产完数据后，如果缓冲区非满就广播信号唤醒其他等待的生产者线程。

 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h> // 增加延时函数所需的头文件

#define BUFFER_SIZE 5  // 缓冲区大小
#define PRODUCER_NUM 2 // 生产者线程数目
#define CONSUMER_NUM 3 // 消费者线程数目

int buffer[BUFFER_SIZE] = {0};                           // 缓冲区，存放待处理数据
int in = 0;                                              // 缓冲区写指针
int out = 0;                                             // 缓冲区读指针
bool buffer_full = false;                                // 缓冲区是否已满
bool buffer_empty = true;                                // 缓冲区是否为空
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;       // 初始化互斥量
pthread_cond_t cond_producer = PTHREAD_COND_INITIALIZER; // 初始化条件变量（生产者）
pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER; // 初始化条件变量（消费者）

void *producer(void *arg)
{
    int id = *(int *)arg;
    free(arg); // 释放传递的参数内存空间
    for (int i = 0; i < BUFFER_SIZE / PRODUCER_NUM; i++)
    {                               // 生产缓冲区中一部分数据
        pthread_mutex_lock(&mutex); // 获取锁
        while (buffer_full)
        { // 如果缓冲区已满，则等待
            pthread_cond_wait(&cond_producer, &mutex);
        }
        buffer[in] = id * (BUFFER_SIZE / PRODUCER_NUM) + i; // 将数据存入缓冲区
        printf("Producer %d produced item %d\n", id, buffer[in]);
        in = (in + 1) % BUFFER_SIZE; // 更新写指针
        buffer_empty = false;        // 标记缓冲区非空
        if (!buffer_full)
        {                                           // 如果缓冲区非满，就通知正在等待的其他生产者线程
            pthread_cond_broadcast(&cond_producer); // 广播信号唤醒等待的生产者线程
        }
        pthread_cond_signal(&cond_consumer); // 发送信号唤醒消费者
        pthread_mutex_unlock(&mutex);        // 释放锁
    }

    usleep(1000000); // 延时500ms
    printf("Producer %d produced item %d\n", id, buffer[in]);

    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int consumed_item;
    while (true)
    {                               // 不断消费数据直到缓冲区为空
        pthread_mutex_lock(&mutex); // 获取锁
        while (buffer_empty)
        { // 如果缓冲区为空，则等待
            pthread_cond_wait(&cond_consumer, &mutex);
        }
        consumed_item = buffer[out]; // 从缓冲区取出数据
        printf("Consumer consumed item %d\n", consumed_item);
        out = (out + 1) % BUFFER_SIZE;
        // 更新读指针
        buffer_full = false; // 标记缓冲区非满
        if (!buffer_empty)
        {                                           // 如果缓冲区非空，就通知正在等待的其他消费者线程
            pthread_cond_broadcast(&cond_consumer); // 广播信号唤醒等待的消费者线程
        }
        if (out == in && buffer_empty)
        { // 如果缓冲区已空并且所有生产者线程都已经结束，则退出循环
            buffer_empty = true;
            pthread_cond_broadcast(&cond_producer); // 通知生产者线程结束
            pthread_mutex_unlock(&mutex);           // 释放锁
            break;
        }
        pthread_mutex_unlock(&mutex); // 释放锁
    }


    usleep(1000000); // 延时500ms

    pthread_exit(NULL);
}

int main()
{
    int i, *producer_id;
    pthread_t producer_threads[PRODUCER_NUM], consumer_threads[CONSUMER_NUM];
    for (i = 0; i < PRODUCER_NUM; i++)
    {
        producer_id = (int *)malloc(sizeof(int)); // 动态分配内存以传递参数
        *producer_id = i;
        pthread_create(&producer_threads[i], NULL, producer, (void *)producer_id);
    }
    for (i = 0; i < CONSUMER_NUM; i++)
    {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }
    for (i = 0; i < PRODUCER_NUM; i++)
    {
        pthread_join(producer_threads[i], NULL);
    }
    for (i = 0; i < CONSUMER_NUM; i++)
    {
        pthread_join(consumer_threads[i], NULL);
    }
    return 0;
}
