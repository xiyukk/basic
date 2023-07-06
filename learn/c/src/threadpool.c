#include <stdlib.h>
#include <unistd.h>
#include "threadpool.h"

// 线程工作函数
void *thread_work(void *arg) {
    threadpool_t *pool = (threadpool_t *)arg;
    task_t *task;

    while (1) {
        pthread_mutex_lock(&(pool->lock));

        // 等待任务队列中有任务
        while (pool->task_queue_size == 0 && !pool->shutdown) {
            pthread_cond_wait(&(pool->cond), &(pool->lock));
        }

        if (pool->shutdown) {
            pthread_mutex_unlock(&(pool->lock));
            pthread_exit(NULL);
        }

        // 获取任务队列中的任务
        task = pool->task_queue_head;
        pool->task_queue_head = task->next;
        pool->task_queue_size--;

        pthread_mutex_unlock(&(pool->lock));

        // 执行任务
        (*(task->function))(task->arg);

        // 释放任务内存
        free(task);
    }

    return NULL;
}

// 创建线程池
threadpool_t *threadpool_create(int thread_count) {
    threadpool_t *pool = (threadpool_t *)malloc(sizeof(threadpool_t));
    if (pool == NULL) {
        return NULL;
    }

    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * thread_count);
    if (pool->threads == NULL) {
        free(pool);
        return NULL;
    }

    pthread_mutex_init(&(pool->lock), NULL);
    pthread_cond_init(&(pool->cond), NULL);
    pool->task_queue_head = NULL;
    pool->thread_count = thread_count;
    pool->task_queue_size = 0;
    pool->shutdown = 0;

    for (int i = 0; i < thread_count; i++) {
        pthread_create(&(pool->threads[i]), NULL, thread_work, (void *)pool);
    }

    return pool;
}

// 向线程池中添加任务
void threadpool_add_task(threadpool_t *pool, void (*function)(void *), void *arg) {
    task_t *new_task = (task_t *)malloc(sizeof(task_t));
    if (new_task == NULL) {
        return;
    }

    new_task->function = function;
    new_task->arg = arg;
    new_task->next = NULL;

    pthread_mutex_lock(&(pool->lock));

    // 将新任务添加到任务队列
    task_t *task_iter = pool->task_queue_head;
    if (task_iter != NULL) {
        while (task_iter->next != NULL) {
            task_iter = task_iter->next;
        }
        task_iter->next = new_task;
    } else {
        pool->task_queue_head = new_task;
    }
    pool->task_queue_size++;

    pthread_cond_signal(&(pool->cond));
    pthread_mutex_unlock(&(pool->lock));
}

// 销毁线程池
void threadpool_destroy(threadpool_t *pool) {
    pthread_mutex_lock(&(pool->lock));
    pool->shutdown = 1;
    pthread_cond_broadcast(&(pool->cond));
    pthread_mutex_unlock(&(pool->lock));

    for (int i = 0; i < pool->thread_count; i++) {
        pthread_join(pool->threads[i], NULL);
    }

    free(pool->threads);
    pthread_mutex_destroy(&(pool->lock));
    pthread_cond_destroy(&(pool->cond));

    task_t *task_iter;
    while (pool->task_queue_head != NULL) {
        task_iter = pool->task_queue_head;
        pool->task_queue_head = pool->task_queue_head->next;
        free(task_iter);
    }

    free(pool);
}