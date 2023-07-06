#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

// 定义需要处理的功能函数
void* func1(void* arg) {
    printf("Function 1 is running\n");
    return NULL;
}

void* func2(void* arg) {
    printf("Function 2 is running\n");
    return NULL;
}

void* func3(void* arg) {
    printf("Function 3 is running\n");
    return NULL;
}

// 命令行参数解析函数
void parse_args(int argc, char** argv, int* func1_enabled, int* func2_enabled, int* func3_enabled) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--func1") == 0) {
            *func1_enabled = 1;
        } else if (strcmp(argv[i], "--func2") == 0) {
            *func2_enabled = 1;
        } else if (strcmp(argv[i], "--func3") == 0) {
            *func3_enabled = 1;
        }
    }
}

// 时间处理函数
double get_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec / 1000000.0;
}

// 打印处理函数
void print_output(char* output) {
    printf("%s\n", output);
}

int main(int argc, char** argv) {
    // 默认情况下所有功能函数均不启用
    int func1_enabled = 0;
    int func2_enabled = 0;
    int func3_enabled = 0;

    // 解析命令行参数
    parse_args(argc, argv, &func1_enabled, &func2_enabled, &func3_enabled);

    // 定义线程句柄
    pthread_t thread1, thread2, thread3;

    // 记录时间并运行功能函数
    double start_time, end_time;
    if (func1_enabled) {
        start_time = get_time();
        pthread_create(&thread1, NULL, func1, NULL);
        pthread_join(thread1, NULL);
        end_time = get_time();
        printf("Function 1 took %f seconds\n", end_time - start_time);
    }
    if (func2_enabled) {
        start_time = get_time();
        pthread_create(&thread2, NULL, func2, NULL);
        pthread_join(thread2, NULL);
        end_time = get_time();
        printf("Function 2 took %f seconds\n", end_time - start_time);
    }
    if (func3_enabled) {
        start_time = get_time();
        pthread_create(&thread3, NULL, func3, NULL);
        pthread_join(thread3, NULL);
        end_time = get_time();
        printf("Function 3 took %f seconds\n", end_time - start_time);
    }

    // 打印输出结果
    print_output("All functions have finished running");

    return 0;
}
