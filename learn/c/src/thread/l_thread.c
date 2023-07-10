#include <stdio.h>
#include <threads.h>

/* 
 * 以下使用了C11标准的<threads.h>库
 */

#if 0
// 创建和管理线程
// 接下来，可以介绍如何使用<threads.h>库中的函数创建和管理线程。以下是创建和等待线程的基本示例：
// 线程函数
int print_hello(void *arg) {
    printf("Hello from thread %d\n", *(int *)arg);
    return 0;
}

int main() {
    thrd_t thread;
    int thread_id = 1;

    // 创建线程
    if (thrd_create(&thread, print_hello, &thread_id) != thrd_success) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    // 等待线程结束
    thrd_join(thread, NULL);

    printf("Thread joined\n");
    return 0;
}

#endif


#if 0
// 接下来，可以介绍如何使用互斥锁进行线程同步。以下是一个简单的示例，演示了如何使用互斥锁保护全局变量，避免竞争条件：
#define NUM_THREADS 5

// 互斥锁
mtx_t counter_mutex;
int counter = 0;

int increment_counter(void *arg) {
    // 获取互斥锁
    mtx_lock(&counter_mutex);

    // 修改全局变量
    counter++;
    printf("Counter: %d\n", counter);

    // 释放互斥锁
    mtx_unlock(&counter_mutex);

    return 0;
}

int main() {
    thrd_t threads[NUM_THREADS];

    // 初始化互斥锁
    mtx_init(&counter_mutex, mtx_plain);

    // 创建线程
    for (int i = 0; i < NUM_THREADS; i++) {
        thrd_create(&threads[i], increment_counter, NULL);
    }

    // 等待线程结束
    for (int i = 0; i < NUM_THREADS; i++) {
        thrd_join(threads[i], NULL);
    }

    // 销毁互斥锁
    mtx_destroy(&counter_mutex);

    return 0;
}

#endif


#if 1
// 条件变量
// 最后，可以介绍如何使用条件变量进行线程间通信。以下是一个示例，演示了如何使用条件变量实现生产者-消费者模型：

#define BUFFER_SIZE 5

// 缓冲区
int buffer[BUFFER_SIZE];
int count = 0;

// 互斥锁和条件变量
mtx_t mutex;
cnd_t not_empty;
cnd_t not_full;

int producer(void *arg) {
    for (int i = 0; i < 10; i++) {
        mtx_lock(&mutex);

        // 等待缓冲区不满
        while (count == BUFFER_SIZE) {
            cnd_wait(&not_full, &mutex);
        }

        // 生产数据
        buffer[count++] = i;
        printf("Produced: %d\n", i);

        // 通知消费者缓冲区非空
        cnd_signal(&not_empty);
        mtx_unlock(&mutex);
    }
    return 0;
}

int consumer(void *arg) {
    for (int i = 0; i < 10; i++) {
        mtx_lock(&mutex);

        // 等待缓冲区非空
        while (count == 0) {
            cnd_wait(&not_empty, &mutex);
        }

        // 消费数据
        int item = buffer[--count];
        printf("Consumed: %d\n", item);

        // 通知生产者缓冲区不满
        cnd_signal(&not_full);
        mtx_unlock(&mutex);
    }
    return 0;
}

int main() {
    thrd_t producer_thread, consumer_thread;

    // 初始化互斥锁和条件变量
    mtx_init(&mutex, mtx_plain);
    cnd_init(&not_empty);
    cnd_init(&not_full);

    // 创建生产者和消费者线程
    thrd_create(&producer_thread, producer, NULL);
    thrd_create(&consumer_thread, consumer, NULL);

    // 等待线程结束
    thrd_join(producer_thread, NULL);
    thrd_join(consumer_thread, NULL);

    // 销毁互斥锁和条件变量
    mtx_destroy(&mutex);
    cnd_destroy(&not_empty);
    cnd_destroy(&not_full);

    return 0;
}
#endif