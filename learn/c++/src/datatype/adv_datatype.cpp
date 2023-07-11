#if 0
#include <iostream>
#include <cstdint> // 用于固定宽度整数类型

// 基本数据类型 - 类型别名和自动类型推导：
using byte = unsigned char; // 类型别名

int main() {
    byte data = 0xFF; // 使用类型别名定义一个字节
    std::cout << "Byte data: " << static_cast<int>(data) << std::endl;

    // 自动类型推导
    auto i = 42; // i 的类型被推导为 int
    auto d = 3.14; // d 的类型被推导为 double

    std::cout << "i: " << i << ", type: int" << std::endl;
    std::cout << "d: " << d << ", type: double" << std::endl;

    return 0;
}
#endif

#if 1
// 复合数据类型 - 指针和引用：
#include <iostream>
#include <vector>
#include <memory>

void process_vector(const std::vector<int> &v) {
    // 使用引用避免复制向量
    for (const auto &i : v) {
        std::cout << i << " ";
    }
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 使用引用
    process_vector(numbers);
    std::cout << std::endl;

    // 指向 vector<int> 类型的智能指针
    auto numbers_ptr = std::make_shared<std::vector<int>>(numbers);

    // 使用智能指针
    process_vector(*numbers_ptr);
    std::cout << std::endl;

    return 0;
}
#endif