#if 1
#include <iostream>
#include <vector>

int main() {
    // 创建一个 int 类型的空 vector
    std::vector<int> numbers;

    // 向 vector 添加元素
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);

    // 使用下标访问 vector 元素
    std::cout << "The second element is: " << numbers[1] << std::endl;

    // 使用范围 for 循环遍历 vector
    std::cout << "The vector contains:";
    for (int num : numbers) {
        std::cout << " " << num;
    }
    std::cout << std::endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <list>

int main() {
    // 创建一个 int 类型的 list
    std::list<int> numbers = {1, 2, 3, 4, 5};

    // 使用迭代器遍历 list
    std::cout << "The list contains:";
    for (std::list<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // 创建一个乱序的 int 类型 vector
    std::vector<int> numbers = {5, 1, 9, 3, 7};

    // 使用 std::sort 对 vector 进行排序
    std::sort(numbers.begin(), numbers.end());

    // 输出排序后的 vector
    std::cout << "Sorted vector:";
    for (int num : numbers) {
        std::cout << " " << num;
    }
    std::cout << std::endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <vector>
#include <algorithm>

// 自定义比较函数，实现降序排序
bool compare_descending(int a, int b) {
    return a > b;
}

int main() {
    // 创建一个乱序的 int 类型 vector
    std::vector<int> numbers = {5, 1, 9, 3, 7};

    // 使用自定义比较函数进行降序排序
    std::sort(numbers.begin(), numbers.end(), compare_descending);

    // 输出排序后的 vector
    std::cout << "Sorted vector in descending order:";
    for (int num : numbers) {
        std::cout << " " << num;
    }
    std::cout << std::endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {5, 1, 9, 3, 7};

    // 使用 Lambda 表达式对 vector 进行降序排序
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) { return a > b; });

    std::cout << "Sorted vector in descending order:";
    for (int num : numbers) {
        std::cout << " " << num;
    }
    std::cout << std::endl;

    return 0;
}
#endif

#if 0
// 使用自定义分配器优化内存管理。例如，为 std::list 定义一个简单的自定义分配器：
#include <iostream>
#include <list>
#include <memory>

template <typename T>
class SimpleAllocator {
public:
using value_type = T;

SimpleAllocator() = default;

template <typename U>
SimpleAllocator(const SimpleAllocator<U>&) noexcept {}

T* allocate(std::size_t n) {
    return static_cast<T*>(::operator new(n * sizeof(T)));
}

void deallocate(T* p, std::size_t) noexcept {
    ::operator delete(p);
}
};

int main() {
    std::list<int, SimpleAllocator<int>> numbers = {1, 2, 3, 4, 5};

    std::cout << "List with custom allocator:";
    for (int num : numbers) {
        std::cout << " " << num;
    }
    std::cout << std::endl;

    return 0;
}
#endif

#if 0

#endif