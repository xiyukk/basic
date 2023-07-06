#include <iostream>
#include <functional>

/* 
std::bind生成一个可调用的对象，它能将一些参数绑定到给定的可调用对象（函数、lambda表达式、函数对象等）。
 */

int add(int a, int b) {
    return a + b;
}

struct Multiply {
    int operator()(int a, int b) const {
        return a * b;
    }
};

int main() {
    // 使用std::bind绑定参数
    auto add_five = std::bind(add, 5, std::placeholders::_1);
    std::cout << "Bind Function: " << add_five(3) << std::endl; // 输出8

    // 使用std::bind绑定参数和函数对象
    auto multiply_by_two = std::bind(Multiply(), std::placeholders::_1, 2);
    std::cout << "Bind Function Object: " << multiply_by_two(3) << std::endl; // 输出6

    // 使用std::bind绑定参数和lambda表达式
    auto subtract_five = std::bind([](int a, int b) {
        return a - b;
    }, std::placeholders::_1, 5);
    std::cout << "Bind Lambda: " << subtract_five(8) << std::endl; // 输出3

    return 0;
}