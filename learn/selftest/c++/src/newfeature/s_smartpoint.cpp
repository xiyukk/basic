#include <iostream>
#include <memory>
#include "l_queue.h"
#include "log3.h"
#include "pic/yang.png"
#include "123.png"
class s_smartpoint
{
private:
    int value;

public:
    s_smartpoint(int value) : value(value)
    {
        std::cout << "value: " << value << std::endl;
    };
    void print_value_double() const
    {
        std::cout << "value's double is " << value * 2 << std::endl;
    }
    ~s_smartpoint()
    {
        std::cout << "析构函数执行" << std::endl;
    };
};

int main()
{
    // creat shared_ptr samrt_point.
    std::shared_ptr<s_smartpoint> ptr1 = std::make_shared<s_smartpoint>(20);
    ptr1->print_value_double();

    // creat unique_ptr smart_point.
    std::unique_ptr<s_smartpoint> ptr2 = std::make_unique<s_smartpoint>(30);
    ptr2->print_value_double();

    return 0;


}
