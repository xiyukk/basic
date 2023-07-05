#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define NUM_THREADS 8

void *task_function(void *arg) {
    int thread_id = *(int*)arg;
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    int i, j;
    for (i = 0; i < 100000000; i++) {
        j = i * i;
    }
    gettimeofday(&end_time, NULL);
    long long elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000LL + (end_time.tv_usec - start_time.tv_usec) / 1000LL;
    printf("Thread %d finished in %lld ms\n", thread_id, elapsed_time);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i;
    for (i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, task_function, &thread_ids[i]);
    }
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
