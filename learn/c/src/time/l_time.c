#include <stdio.h>
#include <time.h>
#include <unistd.h>

#if 0
// 1. 获取系统时间
int main() {
    // 获取当前时间，以time_t类型表示
    time_t current_time = time(NULL);
    printf("Current time (time_t): %ld\n", current_time);

    // 将time_t类型转换为tm结构体
    struct tm *local_time = localtime(&current_time);

    // 打印当前时间
    printf("Current time (tm struct): %d-%02d-%02d %02d:%02d:%02d\n",
        local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday,
        local_time->tm_hour, local_time->tm_min, local_time->tm_sec);

    return 0;
}
#endif


#if 0
// 2. 格式化时间

int main() {
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);

    // 使用strftime函数格式化时间
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local_time);
    printf("Formatted current time: %s\n", buffer);

    return 0;
}
#endif

#if 0
// 3. 计算时间差

int main() {
    // 记录开始时间
    time_t start_time = time(NULL);

    // 模拟耗时操作（睡眠2秒）
    sleep(2);

    // 记录结束时间
    time_t end_time = time(NULL);

    // 计算时间差
    double time_diff = difftime(end_time, start_time);
    printf("Time difference: %.0lf seconds\n", time_diff);

    return 0;
}
#endif

#if 1
// 4. 高精度计时
int main() {
    // 使用clock_gettime记录开始时间
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);

    // 模拟耗时操作（睡眠500毫秒）
    usleep(500000);

    // 使用clock_gettime记录结束时间
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);

    // 计算时间差（以纳秒为单位）
    long time_diff_in_ns = (end_time.tv_sec - start_time.tv_sec) * 1e9
    + (end_time.tv_nsec - start_time.tv_nsec);

    // 转换为毫秒
    double time_diff_in_ms = (double)time_diff_in_ns / 1e6;
    printf("High precision time difference: %.2lf ms\n", time_diff_in_ms);

    return 0;
}
#endif