#include <stdio.h>

#if 0 
// 函数声明，告诉编译器函数的存在
int add_numbers(int a, int b);

// 函数调用演示
int main() {
    int result = add_numbers(3, 4); // 函数调用
    printf("The sum is: %d\n", result);
    return 0;
}

// 函数定义，实现函数的具体功能
int add_numbers(int a, int b) {
    return a + b;
}

#endif

#if 0
/* 
 * 函数参数传递演示：分为值传递和引用传递
 */

// 值传递示例
void increment_value(int a);
// 指针传递示例
void increment_pointer(int *a);

int main() {
    int number = 10;

    increment_value(number);
    printf("After increment_value(): %d\n", number); // 输出 10

    increment_pointer(&number);
    printf("After increment_pointer(): %d\n", number); // 输出 11

    return 0;
}

// 值传递：传递参数的副本，函数内部对副本的修改不会影响原始变量
void increment_value(int a) {
    a++;
}

// 指针传递：传递参数的地址，函数内部对地址的修改会影响原始变量
void increment_pointer(int *a) {
    (*a)++;
}
#endif

#if 0
/*
 * 函数指针演示 
 */

// 函数声明
int add_numbers(int a, int b);
int subtract_numbers(int a, int b);

// 接受函数指针作为参数的函数
int perform_operation(int (*operation)(int, int), int a, int b);

int main() {
    int a = 5, b = 3;

    // 使用函数指针调用 perform_operation
    printf("Add: %d\n", perform_operation(add_numbers, a, b));
    printf("Subtract: %d\n", perform_operation(subtract_numbers, a, b));

    return 0;
}

int add_numbers(int a, int b) {
    return a + b;
}

int subtract_numbers(int a, int b) {
    return a - b;
}

// operation 是一个函数指针，指向接受两个整数参数并返回整数的函数
int perform_operation(int (*operation)(int, int), int a, int b) 
{
    return operation(a, b);
}
#endif

#if 0 
/*
 * 递归函数演示
 */

// 阶乘函数的递归实现
unsigned long factorial(unsigned int n);

int main() {
    unsigned int n = 5;
    unsigned long result = factorial(n);
    printf("%u! = %lu\n", n, result);
    return 0;
}

// 计算 n 的阶乘
unsigned long factorial(unsigned int n) {
    if (n == 0) {
        return 1; // 0! = 1
    } else {
        return n * factorial(n - 1);
    }
}
#endif

#if 1
/* 
 * 变长参数函数演示
 */

#include <stdarg.h>

double average(int count, ...);

int main() {
    printf("Average of 2, 3, 4: %.2f\n", average(3, 2.0, 3.0, 4.0));
    printf("Average of 5, 10, 15: %.2f\n", average(3, 5.0, 10.0, 15.0));
    return 0;
}

double average(int count, ...) {
    double sum = 0.0;

    // 初始化参数列表
    va_list args;
    va_start(args, count);

    // 遍历参数列表并累加值
    for (int i = 0; i < count; i++) {
        sum += va_arg(args, double);
    }

    // 清理参数列表
    va_end(args);

    return sum / count;
}
#endif