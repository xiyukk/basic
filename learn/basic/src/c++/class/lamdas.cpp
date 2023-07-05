#include <iostream>
#include <vector>
#include <algorithm>

int main() 
{
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 定义一个lambda表达式，捕获所有变量（以值方式），接收一个参数，返回参数的平方
    auto square = [=](int num) {
        return num * num;
    };
    std::cout << "Square of 3: " << square(3) << std::endl; // 输出9

    // 定义一个lambda表达式，捕获所有变量（以引用方式），接收一个参数，返回参数加上sum的值
    int sum = 5;
    auto add_sum = [&](int num) { 
        return num + sum;
    };
    std::cout << "3 + sum: " << add_sum(3) << std::endl; // 输出8

    // 使用lambda表达式作为算法参数
    int count = std::count_if(numbers.begin(), numbers.end(), [](int num) {
        return num % 2 == 0;
    });
    std::cout << "Number of even elements: " << count << std::endl; // 输出2

    return 0;
}