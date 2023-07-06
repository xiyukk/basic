#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h> // For backtrace() function
#include <stdbool.h>

// Maximum number of call stack entries to store
#define MAX_CALLSTACK 10

// Original memory allocation functions
static void* (*real_malloc)(size_t) = NULL;
static void (*real_free)(void*) = NULL;

typedef struct allocation_record {
    void* ptr;
    size_t size;
    void* callstack[MAX_CALLSTACK];
    int callstack_size;
    struct allocation_record* next;
} allocation_record;

static allocation_record* allocation_list = NULL;

// Add an allocation record to the list
void add_allocation_record(void* ptr, size_t size) {
    allocation_record* record = (allocation_record*)real_malloc(sizeof(allocation_record));
    record->ptr = ptr;
    record->size = size;
    record->callstack_size = backtrace(record->callstack, MAX_CALLSTACK);
    record->next = allocation_list;
    allocation_list = record;
}

// Remove an allocation record from the list
void remove_allocation_record(void* ptr) {
    allocation_record* prev = NULL;
    for (allocation_record* record = allocation_list; record != NULL; record = record->next) {
        if (record->ptr == ptr) {
            if (prev == NULL) {
                allocation_list = record->next;
            } else {
                prev->next = record->next;
            }
            real_free(record);
            return;
        }
        prev = record;
    }
}

// Custom memory allocation function
void* my_malloc(size_t size) {
    void* ptr = real_malloc(size);
    add_allocation_record(ptr, size);
    return ptr;
}

// Custom memory deallocation function
void my_free(void* ptr) {
    remove_allocation_record(ptr);
    real_free(ptr);
}

// Initialize memory hooks
void init_memory_hooks() {
    if (real_malloc == NULL) {
        real_malloc = malloc;
    }
    if (real_free == NULL) {
        real_free = free;
    }
}

// Analyze remaining allocation records to detect memory leaks
void analyze_memory_leaks() {
    printf("Memory leaks detected:\n");
    for (allocation_record* record = allocation_list; record != NULL; record = record->next) {
        printf("Leaked %zu bytes at %p\n", record->size, record->ptr);
        printf("Callstack:\n");
        backtrace_symbols_fd(record->callstack, record->callstack_size, /*fd=*/1);
        printf("\n");
    }
}

int main() {
    // Test memory allocation and deallocation
    init_memory_hooks();
    int* arr1 = (int*)my_malloc(10 * sizeof(int));
    int* arr2 = (int*)my_malloc(5 * sizeof(int));
    // my_free(arr1);

    // Analyze memory leaks
    analyze_memory_leaks();

    // Clean up remaining allocation records
    my_free(arr2);

    return 0;
}