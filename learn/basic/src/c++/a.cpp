#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 需要执行的函数，将互斥锁作为参数传递
void* threaded_function(void* arg) {
    pthread_mutex_t* mutex = (pthread_mutex_t*)arg;
    int flag = 10;
    while (flag--) {
        // 尝试获取互斥锁
        pthread_mutex_lock(mutex);

        // 在此处执行您的函数，例如：
        printf("Thread ID: %lu\n", pthread_self());

        // 释放互斥锁，让其他线程可以执行
        pthread_mutex_unlock(mutex);
    }

    return NULL;
}

int main() {
    const int NUM_THREADS = 4;
    pthread_t threads[NUM_THREADS];
    pthread_mutex_t mutex;

    // 初始化互斥锁
    pthread_mutex_init(&mutex, NULL);

    // 创建4个线程
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, threaded_function, (void*)&mutex);
    }

    // 等待线程完成
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // 销毁互斥锁
    pthread_mutex_destroy(&mutex);

    return 0;
}