#include <stdio.h>
#include <pthread.h>
#include <time.h>

void log_message(const char *message, pthread_t thread_id) {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime); // 获取当前时间
    timeinfo = localtime(&rawtime); // 转换为本地时间

    // 输出时间戳、线程ID和日志消息
    printf("[%02d:%02d:%02d] [Thread %lu] %s\n",
           timeinfo->tm_hour,
           timeinfo->tm_min,
           timeinfo->tm_sec,
           thread_id,
           message);
}
pthread_mutex_t lock;

void critical_section() {
    pthread_t current_thread_id = pthread_self();

    // 线程尝试获取互斥锁
    log_message("Trying to acquire lock...", current_thread_id);
    pthread_mutex_lock(&lock);

    // 线程进入临界区
    log_message("Lock acquired, entering critical section...", current_thread_id);

    // 在此处执行您的操作（例如，访问共享资源）
    // ...

    // 线程退出临界区
    log_message("Leaving critical section, releasing lock...", current_thread_id);
    pthread_mutex_unlock(&lock);
}
void *thread_func(void *arg) {
    for (int i = 0; i < 5; ++i) {
        critical_section();
    }
    return NULL;
}

int main() {
    const int NUM_THREADS = 4;
    pthread_t threads[NUM_THREADS];

    // 初始化互斥锁
    pthread_mutex_init(&lock, NULL);

    // 创建4个线程
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }

    // 等待线程完成
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // 销毁互斥锁
    pthread_mutex_destroy(&lock);

    return 0;
}