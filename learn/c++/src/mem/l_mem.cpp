#if 1
// 2. 使用 new 和 delete 进行动态内存分配和释放的基本用法。以下是一个简单的示例：

#include <iostream>

// 动态分配整数数组
int* allocate_int_array(int size) {
    // 使用 new 分配内存
    int* arr = new int[size];
    return arr;
}

// 释放整数数组
void deallocate_int_array(int* arr) {
    // 使用 delete 释放内存
    delete[] arr;
}

int main() {
    int size = 5;
    int* arr = allocate_int_array(size);

    for (int i = 0; i < size; ++i) {
        arr[i] = i;
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }

    deallocate_int_array(arr);

    return 0;
}
#endif

#if 0
1. 智能指针 std::unique_ptr、std::shared_ptr 和 std::weak_ptr，以及它们如何简化内存管理。以下是一个 std::shared_ptr 的示例：

#include <iostream>
#include <memory>

// 使用 std::shared_ptr 管理整数数组
std::shared_ptr<int[]> allocate_shared_int_array(int size) {
    // 使用 std::shared_ptr 分配内存
    std::shared_ptr<int[]> arr(new int[size]);
    return arr;
}

int main() {
    int size = 5;
    std::shared_ptr<int[]> arr = allocate_shared_int_array(size);

    for (int i = 0; i < size; ++i) {
        arr[i] = i;
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }

    // 无需手动释放内存，std::shared_ptr 会自动管理

    return 0;
}

#endif

#if 0
// 使用 std::allocator 实现自定义内存池，你需要继承 std::allocator 并覆盖它的 allocate 和 deallocate 成员函数。
// 下面是一个简单的自定义内存池示例，提供了固定大小的内存块分配和回收。

#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class CustomMemoryPool : public std::allocator<T> {
public:
    using size_type = typename std::allocator<T>::size_type;
    using pointer = typename std::allocator<T>::pointer;
    using const_pointer = typename std::allocator<T>::const_pointer;

    // 构造函数
    CustomMemoryPool(size_type pool_size = 1024)
        : m_pool_size(pool_size), m_pool(new char[pool_size]), m_next(m_pool.get()) {}

    // 分配内存
    pointer allocate(size_type n, const_pointer hint = 0) {
        size_type required_bytes = n * sizeof(T);
        if (static_cast<size_type>(m_pool.get() + m_pool_size - m_next) < required_bytes) {
            // 内存不足以分配请求的大小
            throw std::bad_alloc();
        }

        pointer result = reinterpret_cast<pointer>(m_next);
        m_next += required_bytes;
        return result;
    }

    // 回收内存
    void deallocate(pointer p, size_type n) {
        // 由于这是一个简单的示例，我们不会实际回收内存。
        // 在实际应用中，你可能需要一个更复杂的策略来管理内存的分配和回收。
    }

private:
    size_type m_pool_size;
    std::unique_ptr<char[]> m_pool;
    char* m_next;
};

int main() {
    CustomMemoryPool<int> memory_pool(1024);
    std::vector<int, CustomMemoryPool<int>> vec(memory_pool);

    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << "vec[" << i << "] = " << vec[i] << std::endl;
    }

    return 0;
}
#endif

#if 0
1. 内存对齐的概念以及 C++11 中的对齐支持。介绍 alignof 和 alignas 关键字的用法。以下是一个简单的示例：
#include <iostream>

// 使用 alignas 指定对齐要求
struct alignas(16) AlignedData {
    int x;
int y;
int z;
int w;
};

int main() {
    AlignedData data;

    // 使用 alignof 查询对齐要求
    std::cout << "Alignment of AlignedData: " << alignof(AlignedData) << std::endl;

    return 0;
}

#endif

