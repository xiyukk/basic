#if 0
// 结构体 - 高级用法：构造函数和成员函数：
#include <iostream>
#include <string>

struct Person
{
    std::string name;
    int age;

    // 构造函数
    Person(const std::string &n, int a) : name(n), age(a) {}

    // 成员函数
    void print() const
    {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

int main()
{
    Person alice("Alice", 30);
    Person bob("Bob", 28);

    // 使用成员函数
    alice.print();
    bob.print();

    return 0;
}

#endif

#if 0
// 枚举 - 类型安全枚举和位操作：
#include <iostream>

enum class FileMode : unsigned int
{
    None = 0,
    Read = 1 << 0,
    Write = 1 << 1,
    Execute = 1 << 2
};

// 位操作符重载
FileMode operator|(FileMode lhs, FileMode rhs)
{
    return static_cast<FileMode>(
        static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs));
}

FileMode operator&(FileMode lhs, FileMode rhs)
{
    return static_cast<FileMode>(
        static_cast<unsigned int>(lhs) & static_cast<unsigned int>(rhs));
}

int main()
{
    FileMode mode = FileMode::Read | FileMode::Write;

    if ((mode & FileMode::Read) != FileMode::None)
    {
        std::cout << "Read mode is set" << std::endl;
    }

    if ((mode & FileMode::Write) != FileMode::None)
    {
        std::cout << "Write mode is set" << std::endl;
    }

    if ((mode & FileMode::Execute) == FileMode::None)
    {
        std::cout << "Execute mode is not set" << std::endl;
    }

    return 0;
}

#endif

#if 1
// 联合体 - 匿名联合和类型安全访问：
#include <iostream>

struct Data
{
    enum class Type
    {
        Int,
        Float
    } type;

    // 匿名联合
    union
    {
        int i;
        float f;
    };

    // 类型安全访问
    int as_int() const
    {
        if (type == Type::Int)
        {
            return i;
        }
        throw std::runtime_error("Invalid type access");
    }

    float as_float() const
    {
        if (type == Type::Float)
        {
            return f;
        }
        throw std::runtime_error("Invalid type access");
    }
};

int main()
{
    Data data1 = {Data::Type::Int, .i = 42};
    Data data2 = {Data::Type::Float, .f = 3.14f};

    try
    {
        std::cout << "data1 as int: " << data1.as_int() << std::endl;
        std::cout << "data2 as float: " << data2.as_float() << std::endl;

        // 抛出异常，因为 data1 的类型是 Int
        std::cout << "data1 as float: " << data1.as_float() << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}

#endif