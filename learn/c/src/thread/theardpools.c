#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_THREADS 10
#define MAX_QUEUE 1000

typedef struct
{
    void (*function)(void *);
    void *argument;
} threadpool_task_t;

typedef struct
{
    pthread_mutex_t lock;
    pthread_cond_t notify;
    threadpool_task_t queue[MAX_QUEUE];
    int queue_size;
    int head, tail;
    int count;
    int shutdown;
    int started;
    pthread_t thread_id[MAX_THREADS];
} threadpool_t;

void *threadpool_thread(void *threadpool);

int threadpool_init(threadpool_t *pool, int threads)
{
    if (threads < 0 || threads > MAX_THREADS)
    {
        threads = MAX_THREADS;
    }
    pool->queue_size = 0;
    pool->head = pool->tail = pool->count = 0;
    pool->shutdown = pool->started = 0;

    pthread_mutex_init(&(pool->lock), NULL);
    pthread_cond_init(&(pool->notify), NULL);

    for (int i = 0; i < threads; i++)
    {
        pthread_create(&(pool->thread_id[i]), NULL, threadpool_thread, (void *)pool);
        pool->count++;
        pool->started++;
    }
    return 0;
}

int threadpool_add(threadpool_t *pool, void (*function)(void *), void *argument)
{
    int err = 0;
    int next;
    if (pool == NULL || function == NULL)
    {
        return -1;
    }
    pthread_mutex_lock(&(pool->lock));
    next = pool->tail + 1;
    next = (pool->queue_size == MAX_QUEUE) ? 0 : next;
    do
    {
        if (pool->queue_size == MAX_QUEUE)
        {
            err = -1;
            break;
        }
        pool->queue[pool->tail].function = function;
        pool->queue[pool->tail].argument = argument;
        pool->tail = next;
        pool->queue_size += 1;
        if (pthread_cond_signal(&(pool->notify)) != 0)
        {
            err = -1;
            break;
        }
    } while (false);
    pthread_mutex_unlock(&(pool->lock));
    return err;
}

int threadpool_destroy(threadpool_t *pool)
{
    int err = 0;
    if (pool == NULL)
    {
        return -1;
    }
    pthread_mutex_lock(&(pool->lock));
    if (pool->shutdown)
    {
        err = -1;
    }
    else
    {
        pool->shutdown = 1;
        if (pthread_cond_broadcast(&(pool->notify)) != 0)
        {
            err = -1;
        }
        while (pool->count > 0)
        {
            if (pthread_cond_wait(&(pool->notify), &(pool->lock)) != 0)
            {
                err = -1;
                break;
            }
        }
        pthread_mutex_destroy(&(pool->lock));
        pthread_cond_destroy(&(pool->notify));
    }
    pthread_mutex_unlock(&(pool->lock));
    return err;
}

void *threadpool_thread(void *threadpool)
{
    threadpool_t *pool = (threadpool_t *)threadpool;
    threadpool_task_t task;
    while (true)
    {
        pthread_mutex_lock(&(pool->lock));
        while (pool->queue_size == 0 && !pool->shutdown)
        {
            pthread_cond_wait(&(pool->notify), &(pool->lock));
        }
        if (pool->shutdown && !pool->started)
        {
            break;
        }
        task.function = pool->queue[pool->head].function;
        task.argument = pool->queue[pool->head].argument;
        pool->head = (pool->head + 1) % MAX_QUEUE;
        pool->queue_size--;
        pool->started--;
        pthread_mutex_unlock(&(pool->lock));
        (*(task.function))(task.argument);
        pthread_mutex_lock(&(pool->lock));
        pool->started++;
        pthread_mutex_unlock(&(pool->lock));
    }
    pool->count--;
    pthread_mutex_unlock(&(pool->lock));
    pthread_exit(NULL);
    return NULL;
}

void print_hello(void *arg)
{
    int *x = (int *)arg;
    printf("Hello from thread %d\n", *x);
}

int main()
{
    threadpool_t pool;
    threadpool_init(&pool, 4);
    int args[MAX_THREADS];

    for (int i = 0; i < MAX_THREADS; i++)
    {
        args[i] = i;
        threadpool_add(&pool, print_hello, (void *)&args[i]);
    }

    sleep(2);
    threadpool_destroy(&pool);
    return 0;
}