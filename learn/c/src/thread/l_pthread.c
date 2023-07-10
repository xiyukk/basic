#include <stdio.h>
#include <pthread.h>

#if 1
// 线程函数
void *print_hello(void *arg) {
    printf("Hello from thread %d\n", *(int *)arg);
    return NULL;
}

int main() {
    pthread_t thread;
    int thread_id = 1;

    // 创建线程
    if (pthread_create(&thread, NULL, print_hello, &thread_id) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    // 等待线程结束
    pthread_join(thread, NULL);

    printf("Thread joined\n");
    return 0;
}
#endif

#if 0 
#define NUM_THREADS 5

// 互斥锁
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void *increment_counter(void *arg) {
    // 获取互斥锁
    pthread_mutex_lock(&counter_mutex);

    // 修改全局变量
    counter++;
    printf("Counter: %d\n", counter);

    // 释放互斥锁
    pthread_mutex_unlock(&counter_mutex);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // 创建线程
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    // 等待线程结束
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // 销毁互斥锁
    pthread_mutex_destroy(&counter_mutex);

    return 0;
}
#endif

#if 0
#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 5

// 缓冲区
int buffer[BUFFER_SIZE];
int count = 0;

// 互斥锁和条件变量
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);

        // 等待缓冲区不满
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&not_full, &mutex);
        }

        // 生产数据
        buffer[count++] = i;
        printf("Produced: %d\n", i);

        // 通知消费者缓冲区非空
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);

        // 等待缓冲区非空
        while (count == 0) {
            pthread_cond_wait(&not_empty, &mutex);
        }

        // 消费数据
        int item = buffer[--count];
        printf("Consumed: %d\n", item);

        // 通知生产者缓冲区未满
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // 创建生产者和消费者线程
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // 等待线程结束
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // 销毁互斥锁和条件变量
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);

    return 0;
}
#endif