#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define NUM_THREADS 4

// 线程参数结构体
typedef struct {
    int thread_id;
    long long exec_time;
} thread_arg_t;

// 获取当前时间（毫秒）
long long current_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

// 线程函数
void *thread_function(void *arg) {
    thread_arg_t *thread_arg = (thread_arg_t *)arg;
    long long start_time = current_time_ms();

    // 在这里执行您的任务
    sleep(1 + thread_arg->thread_id % 2);

    long long end_time = current_time_ms();
    thread_arg->exec_time = end_time - start_time;

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_arg_t thread_args[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].thread_id = i;
        pthread_create(&threads[i], NULL, thread_function, (void *)&thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        printf("Thread %d execution time: %lld ms\n", i, thread_args[i].exec_time);
    }

    // 注意：计算CPU使用率的方法因操作系统而异，以下代码仅适用于Linux系统
    FILE *fp;
    char buffer[128];
    double cpu_usage;

    fp = popen("grep 'cpu ' /proc/stat | awk '{usage=($2+$4)*100/($2+$4+$5)} END {print usage}'", "r");
    if (fp != NULL) {
        fgets(buffer, sizeof(buffer) - 1, fp);
        cpu_usage = atof(buffer);
        printf("CPU usage: %.2lf%%\n", cpu_usage);
        pclose(fp);
    } else {
        printf("Failed to get CPU usage\n");
    }

    return 0;
}