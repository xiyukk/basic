#if 1
// std::for_each: 遍历容器中的每个元素并对其执行操作。
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 使用lambda表达式打印每个元素
    std::for_each(vec.begin(), vec.end(), [](int x) {
        std::cout << x << " ";
    });
    std::cout << std::endl;

    return 0;
}

#endif

#if 0
// std::transform: 将一个函数应用于一个范围的元素，并将结果存储在另一个范围中。
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::vector<int> result(vec.size());

    // 使用lambda表达式将每个元素平方
    std::transform(vec.begin(), vec.end(), result.begin(), [](int x) {
        return x * x;
    });

    for (const auto& elem : result) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}

#endif

#if 0
// std::sort: 根据提供的比较函数对容器中的元素进行排序。
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {5, 1, 4, 2, 3};

    // 使用lambda表达式按降序排序
    std::sort(vec.begin(), vec.end(), [](int a, int b) {
        return a > b;
    });

    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}

#endif
