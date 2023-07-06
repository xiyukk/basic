#include <stdio.h>
#include <stdlib.h>

// 原始内存分配函数
static void* (*real_malloc)(size_t) = NULL;
static void (*real_free)(void*) = NULL;

// 自定义内存分配函数
void* my_malloc(size_t size) {
    void* ptr = real_malloc(size);
    printf("Allocated %zu bytes at %p\n", size, ptr);
    return ptr;
}

// 自定义内存释放函数
void my_free(void* ptr) {
    printf("Freed memory at %p\n", ptr);
    real_free(ptr);
}

// 初始化内存hook
void init_memory_hooks() {
    if (real_malloc == NULL) {
        real_malloc = malloc;
    }
    if (real_free == NULL) {
        real_free = free;
    }
}

// 清除内存hook
void clear_memory_hooks() {
    // 此函数仅用于演示目的，实际情况可能不需要清除内存hook
}

#define malloc(size) (init_memory_hooks(), real_malloc ? my_malloc(size) : malloc(size))
#define free(ptr) (init_memory_hooks(), real_free ? my_free(ptr) : free(ptr))

int main() {
    // 测试内存分配和释放
    int* arr = (int*)malloc(10 * sizeof(int));
    free(arr);

    return 0;
}