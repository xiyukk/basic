#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

#if 0
// 线程池
#define NUM_THREADS 4
#define MAX_TASKS 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct task_struct {
    void (*func)(void *arg);
    void *arg;
    struct task_struct *next;
} task_t;

task_t *task_queue = NULL;

void *thread_func(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        while (task_queue == NULL) {
            pthread_cond_wait(&cond, &mutex);
        }

        task_t *task = task_queue;
        task_queue = task->next;

        pthread_mutex_unlock(&mutex);

        task->func(task->arg);
        free(task);
    }

    return NULL;
}

void add_task(void (*func)(void *arg), void *arg) {
    task_t *task = malloc(sizeof(task_t));
    task->func = func;
    task->arg = arg;
    task->next = NULL;

    pthread_mutex_lock(&mutex);

    task_t **last = &task_queue;
    while (*last != NULL) {
        last = &((*last)->next);
    }
    *last = task;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

void task_func(void *arg) {
    int id = *(int *)arg;
    printf("Task %d executed by thread %lu\n", id, pthread_self());
    free(arg);
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }

    for (int i = 0; i < MAX_TASKS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        add_task(task_func, id);
    }

    sleep(2);

    return 0;
}
#endif

#if 1
// 线程优先级调度允许您根据线程的优先级为线程分配处理器时间。在实时系统或对性能要求较高的应用中，
// 这种调度策略可能很有用。

void *thread_func(void *arg) {
    int id = *(int *)arg;
    printf("Thread %d started\n", id);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int thread1_id = 1, thread2_id = 2;

    pthread_attr_t attr1, attr2;
    struct sched_param param1, param2;

    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    pthread_attr_setschedpolicy(&attr1, SCHED_FIFO);
    pthread_attr_setschedpolicy(&attr2, SCHED_FIFO);

    param1.sched_priority = sched_get_priority_max(SCHED_FIFO) - 1;
    param2.sched_priority = sched_get_priority_min(SCHED_FIFO);

    pthread_attr_setschedparam(&attr1, &param1);
    pthread_attr_setschedparam(&attr2, &param2);

    pthread_create(&thread1, &attr1, thread_func, &thread1_id);
    pthread_create(&thread2, &attr2, thread_func, &thread2_id);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_attr_destroy(&attr1);
    pthread_attr_destroy(&attr2);

    return 0;
}
#endif