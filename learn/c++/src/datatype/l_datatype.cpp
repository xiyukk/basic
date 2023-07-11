#include <iostream>

#if 0
int main() {
    // 基本数据类型示例
    int a = 42; // 整型
    float b = 3.14f; // 单精度浮点型
    double c = 2.71828; // 双精度浮点型
    char d = 'A'; // 字符型

    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "d: " << d << std::endl;

    return 0;
}
#endif

#if 1
#include <iostream>
#include <array>
#include <string>

int main() {
    // 复合数据类型示例
    // 数组
    int int_array[5] = {1, 2, 3, 4, 5};

    // C++11 标准库提供的 std::array
    std::array<int, 5> int_std_array = {1, 2, 3, 4, 5};

    // 字符串
    std::string str = "Hello, World!";

    // 指针
    int x = 42;
    int *ptr = &x; // 指针变量 ptr 指向整数 x 的地址

    // 打印数组、字符串和指针值
    std::cout << "int_array: ";
    for (int i : int_array) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "int_std_array: ";
    for (int i : int_std_array) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "str: " << str << std::endl;

    std::cout << "x: " << x << ", *ptr: " << *ptr << std::endl;

    return 0;
}
#endif