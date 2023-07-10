#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_POOL_SIZE 1024

typedef struct {
unsigned char pool[MEMORY_POOL_SIZE];
unsigned int used;
} MemoryPool;

void pool_init(MemoryPool *pool) {
    memset(pool->pool, 0, MEMORY_POOL_SIZE);
    pool->used = 0;
}

void *pool_alloc(MemoryPool *pool, size_t size) {
    if (pool->used + size > MEMORY_POOL_SIZE) {
        return NULL; // 内存不足
    }
    void *ptr = pool->pool + pool->used;
    pool->used += size;
    return ptr;
}

int main() {
    MemoryPool pool;
    pool_init(&pool);

    int *arr = (int *)pool_alloc(&pool, 5 * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }else
    {
        // 将内存地址打印为%d（有符号整数）是不正确的。应该使用%p来打印指针地址，
        // 并将arr转换为void *类型。这样，可以正确地显示无符号的内存地址。
        // 使用%p可以确保在不同平台上都能正确显示内存地址。
        printf("arr's address = %p\n", (void *)arr);
        printf("mem alloc sucessfully.\n");
    }
    

    arr[0] = 1;
    arr[1] = 2;
    printf("arr[0] = %d, arr[1] =%d\n", arr[0], arr[1]);

    // 注意：使用内存池时，不需要单独释放内存，因为内存池在作用域结束后会自动释放

    return 0;
}