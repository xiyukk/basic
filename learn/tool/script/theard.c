#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_NUM 2

pthread_mutex_t mutex;
pthread_cond_t cond;
int flag = 0;

void *thread_func(void *arg)
{
    int i, t;
    long tid;

    tid = (long)arg;

    for (i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        while (!flag) {
            printf("Thread %ld waiting...\n", tid);
            pthread_cond_wait(&cond, &mutex);
        }
        printf("Thread %ld: Got the signal!\n", tid);
        flag = 0;
        pthread_mutex_unlock(&mutex);
    }

    printf("Thread %ld finished!\n", tid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int i, ret;
    pthread_t threads[THREAD_NUM];
    pthread_attr_t attr;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    for (i = 0; i < THREAD_NUM; i++) {
        printf("Creating thread %d...\n", i);
        ret = pthread_create(&threads[i], NULL, thread_func, (void *)(long)i);
        if (ret) {
            printf("Error: failed to create thread %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < 5; i++) {
        sleep(1);
        pthread_mutex_lock(&mutex);
        printf("Sending signal...\n");
        flag = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    for (i = 0; i < THREAD_NUM; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    printf("All threads finished!\n");

    return 0;
}
