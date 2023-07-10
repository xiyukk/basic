#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


#if 0
/* 1. 读写锁
 *    读写锁允许多个线程同时读共享资源，但在写入时只允许一个线程。
 *    这可以提高并发性能，特别是当读操作远多于写操作时。以下是一个简单的示例，演示了如何使用读写锁： 
 */
#define NUM_READERS 5
#define NUM_WRITERS 2
// 读写锁
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
int shared_data = 0;

void *reader(void *arg) {
    int id = *(int *)arg;

    // 获取读锁
    pthread_rwlock_rdlock(&rwlock);

    // 读取共享数据
    printf("Reader %d: %d\n", id, shared_data);

    // 释放读锁
    pthread_rwlock_unlock(&rwlock);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    // 获取写锁
    pthread_rwlock_wrlock(&rwlock);

    // 修改共享数据
    shared_data++;
    printf("Writer %d: %d\n", id, shared_data);

    // 释放写锁
    pthread_rwlock_unlock(&rwlock);

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];

    // 创建读者和写者线程
    for (int i = 0; i < NUM_READERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&readers[i], NULL, reader, id);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&writers[i], NULL, writer, id);
    }

    // 等待线程结束
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // 销毁读写锁
    pthread_rwlock_destroy(&rwlock);

    return 0;
}
#endif

#if 0
// 2. 信号量
// 信号量是一种同步原语，用于控制对共享资源的访问。以下是一个简单的示例，演示了如何使用信号量实现生产者-消费者模型：

#define BUFFER_SIZE 5

// 缓冲区
int buffer[BUFFER_SIZE];
int count = 0;

// 信号量
sem_t empty, full;

void *producer(void *arg) {
    for (int i = 0; i < 10; i++) {
        // 等待空槽位
        sem_wait(&empty);

        // 生产数据
        buffer[count++] = i;
        printf("Produced: %d\n", i);

        // 释放满槽位
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < 10; i++) {
        // 等待满槽位
        sem_wait(&full);

        // 消费数据
        int item = buffer[--count];
        printf("Consumed: %d\n", item);

        // 释放空槽位
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // 初始化信号量
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // 创建生产者和消费者线程
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // 等待线程结束
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // 销毁信号量
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
#endif

#if 1
// 3. 屏障
// 屏障（pthread_barrier_t）可以让一组线程在某个点上相互等待，直到所有线程都到达该点后才继续执行。
// 以下是一个简单的示例，演示了如何使用屏障：

#define NUM_THREADS 5

// 屏障
pthread_barrier_t barrier;

void *worker(void *arg) {
    int id = *(int *)arg;

    printf("Thread %d: Before barrier\n", id);

    // 等待所有线程到达屏障
    pthread_barrier_wait(&barrier);

    printf("Thread %d: After barrier\n", id);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // 初始化屏障
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    // 创建工作线程
    for (int i = 0; i < NUM_THREADS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&threads[i], NULL, worker, id);
    }

    // 等待线程结束
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // 销毁屏障
    pthread_barrier_destroy(&barrier);

    return 0;
}
// 这个示例中，屏障确保了所有工作线程在打印 "Before barrier" 消息后，才会打印 "After barrier" 消息。

#endif