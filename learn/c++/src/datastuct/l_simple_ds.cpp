#include <iostream>
#include <string>

#if 0
struct Person
{
    std::string name;
    int age;
};

int main()
{
    // 结构体示例
    Person alice = {"Alice", 30};
    Person bob = {"Bob", 28};

    // 访问结构体成员
    std::cout << "Alice - Name: " << alice.name << ", Age: " << alice.age << std::endl;
    std::cout << "Bob - Name: " << bob.name << ", Age: " << bob.age << std::endl;

    return 0;
}
#endif

#if 0

enum class Color
{
    Red,
    Green,
    Blue
};

int main()
{
    // 枚举示例
    Color color = Color::Red;

    switch (color)
    {
    case Color::Red:
        std::cout << "Color is Red" << std::endl;
        break;
    case Color::Green:
        std::cout << "Color is Green" << std::endl;
        break;
    case Color::Blue:
        std::cout << "Color is Blue" << std::endl;
        break;
    }

    return 0;
}
#endif

#if 1
#include <iostream>

union Value
{
    int i;
    float f;
};

int main()
{
    // 联合体示例
    Value value;
    value.i = 42;

    // 访问联合体成员
    std::cout << "Value as int: " << value.i << std::endl;

    value.f = 3.14f;
    std::cout << "Value as float: " << value.f << std::endl;

    return 0;
}
#endif