#if 1
#include <iostream>
#include <vector>

int main() {
    // 常用用法：使用auto推断简单类型
    auto i = 42; // int
    auto d = 3.14; // double

    // 高级用法：使用auto推断迭代器类型
    std::vector<int> vec = {1, 2, 3, 4, 5};
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
#endif

#if 0

// 范围for循环提供了一种简洁的方法来遍历容器中的元素。

#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 常用用法：遍历容器中的元素
    for (const auto& elem : vec) {
        std::cout << elem << " ";
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
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 常用用法：定义简单的lambda表达式
    auto square = [](int x) { return x * x; };
    std::cout << "Square of 4: " << square(4) << std::endl;

    // 高级用法：使用lambda表达式作为函数参数
    int threshold = 3;
    auto greater_than_threshold = [threshold](int x) { return x > threshold; };
    int count = std::count_if(vec.begin(), vec.end(), greater_than_threshold);
    std::cout << "Number of elements greater than " << threshold << ": " << count << std::endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <memory>

class MyClass {
public:
MyClass(int value) : value_(value) {}
~MyClass() { std::cout << "Destructor called for value: " << value_ << std::endl; }

int value() const { return value_; }

private:
int value_;
};

int main() {
    // 常用用法：使用 shared_ptr 管理内存
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>(42);
    std::shared_ptr<MyClass> ptr2 = ptr1; // 多个 shared_ptr 可共享同一个对象

    // 高级用法：使用 unique_ptr 管理内存
    std::unique_ptr<MyClass> ptr3 = std::make_unique<MyClass>(84);
    // std::unique_ptr<MyClass> ptr4 = ptr3; // 错误：unique_ptr 不允许拷贝
    std::unique_ptr<MyClass> ptr4 = std::move(ptr3); // 转移对象的所有权

    return 0;
}
#endif

