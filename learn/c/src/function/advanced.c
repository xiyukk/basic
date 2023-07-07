#include <stdio.h>

/* 
 * 函数指针的高级用法
 */
#if 0

// 函数原型
int add(int a, int b);
int subtract(int a, int b);

// 函数指针类型
typedef int (*operation)(int, int);

// 使用函数指针调用操作的高阶函数
int perform_operation(int a, int b, operation op) {
    return op(a, b);
}

int main() {
    int a = 5, b = 3;

    // 使用add和subtract函数指针
    operation add_op = add;
    operation sub_op = subtract;

    printf("Add: %d\n", perform_operation(a, b, add_op));
    printf("Subtract: %d\n", perform_operation(a, b, sub_op));

    return 0;
}

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

#endif

#if 0
/* 
 * 回调函数
 */

// 比较函数类型
typedef int (*compare)(int, int);

// 交换函数
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 通用冒泡排序函数
void bubble_sort(int arr[], int size, compare cmp) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (cmp(arr[j], arr[j + 1]) > 0) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// 比较函数：升序和降序
int ascending(int a, int b) {
    return a - b;
}

int descending(int a, int b) {
    return b - a;
}

// 打印数组
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {5, 3, 1, 4, 2};
    int size = sizeof(arr) / sizeof(arr[0]);

    bubble_sort(arr, size, ascending);
    printf("Ascending order: ");
    print_array(arr, size);

    bubble_sort(arr, size, descending);
    printf("Descending order: ");
    print_array(arr, size);

    return 0;
}
#endif

#if 1
/* 
 * c语言本身没有匿名函数，使用嵌套函数和函数指针来模拟匿名函数
 */

// 高阶函数，接受一个函数指针作为参数
void call_function(void (*func)(const char *)) {
    func("Hello, world!");
}

int main() {
    // 使用GCC扩展定义一个嵌套函数
    void my_print(const char *msg) {
        printf("%s\n", msg);
    }

    // 将嵌套函数作为参数传递给高阶函数
    call_function(my_print);

    return 0;
}
#endif