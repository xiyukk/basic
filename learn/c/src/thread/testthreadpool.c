#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define MAX_THREADS 5
#define TASKS_COUNT 2

void *thread_function(void *arg);
sem_t semaphore;

int main() {
    pthread_t threads[MAX_THREADS];
    sem_init(&semaphore, 0, 0);
    // printf("-----------------------------------------------------\n");

    // 创建线程
    for(int i = 0; i < MAX_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_function, NULL);
    }

    // 提交任务
    for(int i = 0; i < TASKS_COUNT; i++) {
        sem_post(&semaphore);
    }

    // 等待所有任务完成
    for(int i = 0; i < TASKS_COUNT; i++) {
        sem_wait(&semaphore);
    }

    // 结束线程
    for(int i = 0; i < MAX_THREADS; i++) {
        pthread_cancel(threads[i]);
    }

    sem_destroy(&semaphore);
    return 0;
}

void *thread_function(void *arg) {
    while(1) {
        sem_wait(&semaphore);
        // 执行任务
        // 注意：这里应该放入你的任务代码
        printf("Task is being executed by thread %ld\n", pthread_self());
        sem_post(&semaphore);
    }
    return NULL;
}
