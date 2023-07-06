/* #include <functional>
#include <iostream>
std::function<void(int)> f; // 这里表示function的对象f的参数是int，返回值是void

struct Foo
{
    Foo(int num) : num_(num) {}
    void print_add(int i) const { std::cout << num_ + i << '\n'; }
    int num_;
};

void print_num(int i) { std::cout << i << '\n'; }

struct PrintNum
{
    void operator()(int i) const { std::cout << i << '\n'; }
};

int main()
{
    // 存储自由函数
    std::function<void(int)> f_display = print_num;
    f_display(-9);

    // 存储 lambda
    std::function<void()> f_display_42 = []()
    { print_num(42); };
    f_display_42();

    // 存储到 std::bind 调用的结果
    std::function<void()> f_display_31337 = std::bind(print_num, 31337);
    f_display_31337();

    // 存储到成员函数的调用
    std::function<void(const Foo &, int)> f_add_display = &Foo::print_add;
    const Foo foo(314159);
    f_add_display(foo, 1);
    f_add_display(314159, 1);

    // 存储到数据成员访问器的调用
    std::function<int(Foo const &)> f_num = &Foo::num_;
    std::cout << "num_: " << f_num(foo) << '\n';

    // 存储到成员函数及对象的调用
    using std::placeholders::_1;
    std::function<void(int)> f_add_display2 = std::bind(&Foo::print_add, foo, _1);
    f_add_display2(2);

    // 存储到成员函数和对象指针的调用
    std::function<void(int)> f_add_display3 = std::bind(&Foo::print_add, &foo, _1);
    f_add_display3(3);

    // 存储到函数对象的调用
    std::function<void(int)> f_display_obj = PrintNum();
    f_display_obj(18);
} */


/* 

std::function是一个通用、多态的函数封装器。
它的实例可以存储、复制和调用任何可调用的目标（函数、lambda表达式、函数对象等）。
 */

#include <iostream>
#include <functional>

// 定义一个简单的函数
int add(int a, int b) {
    return a + b;
}

// 定义一个函数对象
struct Multiply {
    int operator()(int a, int b) const {
        return a * b;
    }
};

int main() {
    // 使用std::function封装函数
    std::function<int(int, int)> func1 = add;
    std::cout << "Function: " << func1(3, 5) << std::endl; // 输出8

    // 使用std::function封装函数对象
    std::function<int(int, int)> func2 = Multiply();
    std::cout << "Function Object: " << func2(3, 5) << std::endl; // 输出15

    // 使用std::function封装lambda表达式
    std::function<int(int, int)> func3 = [](int a, int b) {
        return a - b;
    };
    std::cout << "Lambda: " << func3(3, 5) << std::endl; // 输出-2

    return 0;
}