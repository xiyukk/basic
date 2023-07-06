#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_POOL_SIZE 4
#define QUEUE_SIZE 100

typedef struct {
    void (*function)(void *);
    void *argument;
} task;

typedef struct {
    task tasks[QUEUE_SIZE];
    int front;
    int rear;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} thread_pool;

void initialize_thread_pool(thread_pool *pool) {
    pool->front = 0;
    pool->rear = 0;
    pool->count = 0;
    pthread_mutex_init(&pool->mutex, NULL);
    pthread_cond_init(&pool->not_empty, NULL);
    pthread_cond_init(&pool->not_full, NULL);
}

void add_task(thread_pool *pool, void (*function)(void *), void *argument) {
    pthread_mutex_lock(&pool->mutex);
    while (pool->count == QUEUE_SIZE) {
        pthread_cond_wait(&pool->not_full, &pool->mutex);
    }
    pool->tasks[pool->rear].function = function;
    pool->tasks[pool->rear].argument = argument;
    pool->rear = (pool->rear + 1) % QUEUE_SIZE;
    pool->count++;
    pthread_cond_signal(&pool->not_empty);
    pthread_mutex_unlock(&pool->mutex);
}

void execute_task(thread_pool *pool) {
    task task;
    pthread_mutex_lock(&pool->mutex);
    while (pool->count == 0) {
        pthread_cond_wait(&pool->not_empty, &pool->mutex);
    }
    task = pool->tasks[pool->front];
    pool->front = (pool->front + 1) % QUEUE_SIZE;
    pool->count--;
    pthread_cond_signal(&pool->not_full);
    pthread_mutex_unlock(&pool->mutex);
    (*task.function)(task.argument);
}

void *worker_thread(void *arg) {
    thread_pool *pool = arg;
    while (1) {
        execute_task(pool);
    }
}

void start_thread_pool(thread_pool *pool) {
    int i;
    pthread_t thread;
    for (i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&thread, NULL, worker_thread, pool);
        pthread_detach(thread);
    }
}

void task_function(void *argument) {
    int *number = argument;
    printf("Task %d is running.\n", *number);
}

int main() {
    int i;
    thread_pool pool;
    initialize_thread_pool(&pool);
    start_thread_pool(&pool);
    for (i = 0; i < 40; i++) {
        int *number = malloc(sizeof(int));
        *number = i;
        add_task(&pool, task_function, number);
    }
    sleep(1);
    return 0;
}