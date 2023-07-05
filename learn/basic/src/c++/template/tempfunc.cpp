#include <iostream>
#include <tuple>

// 类模板声明
template <typename T>
class MyClass {
public:
    // 可变参数模板函数声明
    template <typename... Args>
    void print(Args... args) {
        auto values = std::make_tuple(args...); // 将传入的参数转换为元组
        print_impl(values, std::index_sequence_for<Args...>{}); // 调用实现函数
    }

private:
    // 实现函数，使用index_sequence展开参数包
    template <typename Tuple, size_t... Is>
    void print_impl(const Tuple& values, std::index_sequence<Is...>) {
        ((std::cout << "Value " << Is << ": " << std::get<Is>(values) << std::endl), ...);
    }
};

int main() {
    MyClass<int> obj; // 实例化模板类，T = int
    obj.print(1, "hello", 3.14); // 调用可变参数模板函数，Args = {int, const char*, double}
    return 0;
}