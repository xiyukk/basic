/* 
 * 宏定义和头文件包含
 */

#if 0
// 宏定义
#define PI 3.14159

// 包含标准库头文件
#include <stdio.h>

// 包含自定义头文件
// #include "my_header.h"

int main() {
    double area = PI * 5.0 * 5.0;
    printf("Area of the circle: %f\n", area);
    return 0;
}

#endif

#if 0
/* 
 * 条件编译
 */
// 根据编译时的条件定义宏
#if defined(_WIN32) || defined(_WIN64)
#define PLATFORM "Windows"
#elif defined(__APPLE__) && defined(__MACH__)
#define PLATFORM "macOS"
#elif defined(__linux__)
#define PLATFORM "Linux"
#else
#define PLATFORM "Unknown"
#endif

int main() {
    printf("Running on %s\n", PLATFORM);
    return 0;
}
#endif

#if 0
/* 
 * 宏函数
 */
// 定义宏函数
#define SQUARE(x) ((x) * (x))

int main() {
    int num = 4;
    int squared = SQUARE(num);
    printf("%d squared is %d\n", num, squared);
    return 0;
}
#endif

#if 0

/* 
 * 防止头文件重复包含
 */
#ifndef MY_HEADER_H
#define MY_HEADER_H

// 声明函数和变量

#endif // MY_HEADER_H
#endif

#if 1 
/* 
 * 使用预处理指令进行调试
 */
// 定义调试宏
#define DEBUG

// 根据是否定义DEBUG宏使用不同的printf
#ifdef DEBUG
#define debug_printf(...) printf(__VA_ARGS__)
#else
#define debug_printf(...)
#endif

int main() {
    int a = 10;
    int b = 20;
    int sum = a + b;

    debug_printf("a: %d, b: %d\n", a, b);
    printf("Sum: %d\n", sum);

    return 0;
}
#endif