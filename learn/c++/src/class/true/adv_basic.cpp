#if 0
/* 2.6 友元函数
友元函数是一个不属于类的成员函数，但可以访问类的私有和受保护成员。要将一个函数声明为类的友元，
需要在类定义中使用 friend 关键字。 */

#include <iostream>

class Box {
public:
Box(int l, int w, int h) : length(l), width(w), height(h) {}

// 声明一个友元函数，它可以访问 Box 类的私有成员
friend int calculate_volume(const Box& box);

private:
int length;
int width;
int height;
};

int calculate_volume(const Box& box) {
    return box.length * box.width * box.height;
}

int main() {
    Box box1(3, 4, 5);

    int volume = calculate_volume(box1);
    std::cout << "Volume of the box: " << volume << std::endl;

    return 0;
}

#endif

#if 0
/* 2.7 运算符重载
运算符重载允许我们为用户自定义类型重新定义运算符的行为。这使得我们可以像操作内置类型那样操作自定义类型。 */
#include <iostream>

class Complex {
public:
Complex(double real, double imag) : real(real), imag(imag) {}

// 重载加法运算符
Complex operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

// 重载输出运算符
friend std::ostream& operator<<(std::ostream& os, const Complex& c);

private:
double real;
double imag;
};

// 重载输出运算符，注意这里是一个友元函数
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real << " + " << c.imag << "i";
    return os;
}

int main() {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);

    Complex c3 = c1 + c2;

    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;
    std::cout << "c3: " << c3 << std::endl;

    return 0;
}

#endif

#if 0
/* 2.8 模板类
模板类允许我们为多种类型创建通用的类定义。这有助于减少代码重复和提高代码复用性。 */

#include <iostream>

template <typename T>
class Pair {
public:
Pair(const T& first, const T& second) : first(first), second(second) {}

T get_first() const {
    return first;
}

T get_second() const {
    return second;
}

private:
T first;
T second;
};

int main() {
    // 使用 int 类型实例化 Pair 模板类
    Pair<int> int_pair(1, 2);
    std::cout << "int_pair: (" << int_pair.get_first()
        << ", " << int_pair.get_second() << ")" << std::endl;

    // 使用 std::string 类型实例化 Pair 模板类
    Pair<std::string> str_pair("Hello", "World");
    std::cout << "str_pair: (" << str_pair.get_first()
        << ", " << str_pair.get_second() << ")" << std::endl;

    return 0;
}

#endif

#if 0
/* 3.1 Lambda 表达式（C++11）
Lambda 表达式是一种创建临时函数对象的简便方法。Lambda 表达式可以捕获外部变量，并在其主体中使用。 */
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 声明一个 lambda 表达式，将每个元素乘以 2
    auto multiply_by_two = [](int x) { return x * 2; };

    // 使用 lambda 表达式对容器中的每个元素执行操作
    std::transform(numbers.begin(), numbers.end(), numbers.begin(), multiply_by_two);

    // 输出结果
    for (int number : numbers) {
        std::cout << number << " " <<std::endl;
    }

    return 0;
}

#endif

#if 0
/* 3.2 智能指针（C++11）
智能指针是一种在堆上分配内存时自动管理内存释放的对象。它们有助于减少内存泄漏和手动管理内存的复杂性。 */

#include <iostream>
#include <memory>

class MyClass {
public:
MyClass(int value) : value(value) {}

void print_value() const {
    std::cout << "Value: " << value << std::endl;
}

private:
int value;
};

int main() {
    // 创建一个 std::shared_ptr 智能指针
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>(10);
    ptr1->print_value();

    // 创建一个 std::unique_ptr 智能指针
    std::unique_ptr<MyClass> ptr2 = std::make_unique<MyClass>(20);
    ptr2->print_value();

    return 0;
}

#endif

#if 1
/* 3.3 右值引用（C++11）
右值引用允许我们捕获临时对象，并避免在移动语义中创建不必要的副本，从而提高性能。 */

#include <iostream>
#include <vector>
#include <string>

class MyString {
public:
MyString(const char* str) : data_(str) {
    std::cout << "Constructed: " << data_ << std::endl;
}

MyString(const MyString& other) : data_(other.data_) {
    std::cout << "Copied: " << data_ << std::endl;
}

MyString(MyString&& other) noexcept : data_(std::move(other.data_)) {
    std::cout << "Moved: " << data_ << std::endl;
}

const std::string& data() const {
    return data_;
}

private:
std::string data_;
};

int main() {
    std::vector<MyString> string_storage;

    // 使用 push_back 复制对象
    std::cout << "Copying:" << std::endl;
    MyString hello("Hello");
    string_storage.push_back(hello);

    // 使用 emplace_back 移动对象
    std::cout << "Moving:" << std::endl;
    string_storage.emplace_back("World");

    return 0;
}

#endif

#if 0

#endif

#if 0

#endif

#if 0

#endif

#if 0

#endif

#if 0

#endif

#if 0

#endif