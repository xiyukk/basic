#include <iostream>

// 定义一个模板类：Pair
// T1和T2是模板参数，表示Pair类可以接受两种不同的数据类型
template <typename T1, typename T2>
class Pair {
public:
    // 构造函数
    Pair(const T1& first, const T2& second)
        : first_(first), second_(second) {}

    // 获取first元素的值
    T1 get_first() const {
        return first_;
    }

    // 获取second元素的值
    T2 get_second() const {
        return second_;
    }

    // 设置first元素的值
    void set_first(const T1& first) {
        first_ = first;
    }

    // 设置second元素的值
    void set_second(const T2& second) {
        second_ = second;
    }

private:
    // Pair类中的数据成员
    T1 first_;
    T2 second_;
};

int main() {
    // 实例化Pair模板类，使用int和std::string作为模板参数
    Pair<int, std::string> pair(1, "one");

    // 输出pair的first和second元素的值
    std::cout << "Pair: (" << pair.get_first() << ", " << pair.get_second() << ")" << std::endl;

    // 修改pair的first和second元素的值
    pair.set_first(2);
    pair.set_second("two");

    // 输出修改后的pair的first和second元素的值
    std::cout << "Modified Pair: (" << pair.get_first() << ", " << pair.get_second() << ")" << std::endl;

    // 实例化Pair模板类，使用double和char作为模板参数
    Pair<double, char> pair2(3.14, 'A');

    // 输出pair2的first和second元素的值
    std::cout << "Pair 2: (" << pair2.get_first() << ", " << pair2.get_second() << ")" << std::endl;

    return 0;
}