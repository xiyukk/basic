#if 1
/* 函数模板允许您为多种类型编写通用的函数。这样可以避免为每种类型编写重复的代码。
以下是一个简单示例，演示了如何使用函数模板实现一个通用的swap函数： */
#include <iostream>

// 函数模板声明，用于交换两个值
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    int i1 = 1, i2 = 2;
    swap(i1, i2); // 使用整数类型实例化swap函数模板
    std::cout << "Swapped integers: " << i1 << ", " << i2 << std::endl;

    double d1 = 1.1, d2 = 2.2;
    swap(d1, d2); // 使用双精度浮点数类型实例化swap函数模板
    std::cout << "Swapped doubles: " << d1 << ", " << d2 << std::endl;

    return 0;
}
#endif

#if 0
/* 类模板允许您为多种类型编写通用的类。
下面是一个简单示例，展示了如何使用类模板创建一个简单的通用堆栈数据结构： */
#include <iostream>
#include <vector>

// 类模板声明，用于定义一个通用堆栈
template <typename T>
class Stack {
public:
// 将元素压入堆栈
void push(const T& item) {
    data.push_back(item);
}

// 弹出堆栈顶部的元素
T pop() {
    if (empty()) {
        throw std::runtime_error("Attempt to pop from an empty stack");
    }

    T item = data.back();
    data.pop_back();
    return item;
}

// 检查堆栈是否为空
bool empty() const {
    return data.empty();
}

private:
std::vector<T> data;
};

int main() {
    Stack<int> int_stack;
    int_stack.push(1);
    int_stack.push(2);
    std::cout << "Popped integer: " << int_stack.pop() << std::endl;

    Stack<std::string> string_stack;
    string_stack.push("Hello");
    string_stack.push("World");
    std::cout << "Popped string: " << string_stack.pop() << std::endl;

    return 0;
}
#endif

#if 0
/* 模板特化允许为特定类型或条件提供特定的模板版本。
以下是一个示例，演示了如何为std::vector<bool>特化前面的Stack类模板，以使用更高效的std::vector<bool>实现： */
#include <iostream>
#include <vector>

template <typename T>
class Stack {
public:
void push(const T& item) {
    data.push_back(item);
}

T pop() {
    if (empty()) {
        throw std::runtime_error("Attempt to pop from an empty stack");
    }

    T item = data.back();
    data.pop_back();
    return item;
}

bool empty() const {
    return data.empty();
}

private:
std::vector<T> data;
};

// Stack模板特化，用于处理std::vector<bool>
template <>
class Stack<bool> {
public:
void push(bool item) {
    data.push_back(item);
}

bool pop() {
    if (empty()) {
        throw std::runtime_error("Attempt to pop from an empty stack");
    }

    bool item = data.back();
    data.pop_back();
    return item;
}

bool empty() const {
    return data.empty();
}

private:
std::vector<bool> data;
};

int main() {
    Stack<bool> bool_stack;
    bool_stack.push(true);
    bool_stack.push(false);
    std::cout << "Popped boolean: " << std::boolalpha << bool_stack.pop() << std::endl;

    return 0;
}
#endif

#if 0
// 可变模板函数允许您创建一个接受可变数量参数的函数。以下示例展示了如何使用可变模板实现一个简单的print_all函数，该函数可以接受任意数量和类型的参数，并将它们打印到标准输出。
#include <iostream>

// 可变模板函数的基本情况，没有参数
void print_all() {
    std::cout << std::endl;
}

// 可变模板函数，接受一个参数 T 和一个参数包 Args
template <typename T, typename... Args>
void print_all(const T& first, const Args&... rest) {
    std::cout << first << " ";
    print_all(rest...); // 递归调用，传递参数包的剩余部分
}

int main() {
    print_all(1, 2.0, "three", 4, 5.0f, '6');
    return 0;
}

#endif

#if 0
// 可变模板类允许您创建一个接受可变数量模板参数的类。以下示例展示了如何使用可变模板实现一个简单的Tuple类，该类可以存储任意数量和类型的值。
#include <iostream>

// 可变模板类的基本情况，没有类型参数
class Tuple {};

// 可变模板类，接受一个类型 T 和一个类型包 Types
template <typename T, typename... Types>
class Tuple<T, Types...> : public Tuple<Types...> {
public:
Tuple(const T& value, const Types&... rest)
: Tuple<Types...>(rest...), value(value) {}

T value;
};

// 函数模板用于获取 Tuple 的第 i 个元素
template <int i, typename T, typename... Types>
typename std::enable_if<i == 0, T>::type& get(Tuple<T, Types...>& tuple) {
    return tuple.value;
}

template <int i, typename T, typename... Types>
typename std::enable_if<i != 0, T>::type& get(Tuple<T, Types...>& tuple) {
    return get<i - 1>(static_cast<Tuple<Types...>&>(tuple));
}

int main() {
    Tuple<int, double, std::string> tuple(1, 2.0, "three");

    std::cout << "Tuple elements: ";
    std::cout << get<0>(tuple) << ", ";
    std::cout << get<1>(tuple) << ", ";
    std::cout << get<2>(tuple) << std::endl;

    return 0;
}

#endif

#if 0
// 下面的示例展示了如何为一个类编写一个成员函数，该函数可以接受任意数量和类型的参数。

#include <iostream>

class Printer {
public:
// 可变模板成员函数的基本情况，没有参数
void print() {
    std::cout << std::endl;
}

// 可变模板成员函数，接受一个参数 T 和一个参数包 Args
template <typename T, typename... Args>
void print(const T& first, const Args&... rest) {
    std::cout << first << " ";
    print(rest...); // 递归调用，传递参数包的剩余部分
}
};

int main() {
    Printer printer;
    printer.print(1, 2.0, "three", 4, 5.0f, '6');
    return 0;
}

#endif

#if 0
使用可变模板实现一个通用的accumulator函数，该函数可以接受任意数量和类型的参数，并计算它们的和。
#include <iostream>

// 可变模板函数的基本情况，没有参数
template <typename T>
T accumulator(const T& value) {
    return value;
}

// 可变模板函数，接受一个参数 T 和一个参数包 Args
template <typename T, typename... Args>
T accumulator(const T& first, const Args&... rest) {
    return first + accumulator(rest...); // 递归调用，将参数包的剩余部分传递给accumulator
}

int main() {
    int sum = accumulator(1, 2, 3, 4, 5);
    std::cout << "Sum of integers: " << sum << std::endl;

    double d_sum = accumulator(1.1, 2.2, 3.3, 4.4, 5.5);
    std::cout << "Sum of doubles: " << d_sum << std::endl;

    return 0;
}

#endif

#if 0
/* 
以下示例展示了如何实现一个通用的apply函数，该函数可以接受一个函数指针和任意数量和类型的参数，并将这些参数应用到给定的函数。
在这个示例中，apply函数使用可变模板来接受一个函数指针和一组参数。apply函数将这些参数应用到给定的函数，并返回结果。请注意，虽然这个示例是用于演示目的，但C++标准库已经提供了一个类似的函数std::apply，您应该在实际编程中使用它。
 */
#include <iostream>

// 示例函数
int add(int a, int b) {
    return a + b;
}

// 示例函数
std::string concatenate(const std::string& a, const std::string& b) {
    return a + b;
}

// 可变模板函数，接受一个函数指针 F 和一个参数包 Args
template <typename R, typename... Args>
R apply(R (*func)(Args...), Args... args) {
    return func(args...);
}

int main() {
    int sum = apply(add, 3, 4);
    std::cout << "Sum of 3 and 4: " << sum << std::endl;

    std::string concatenated = apply(concatenate, "Hello, ", "world!");
    std::cout << "Concatenated strings: " << concatenated << std::endl;

    return 0;
}
#endif

#if 0

#endif