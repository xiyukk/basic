// test deep copy and shallow copy
#include <iostream>
using namespace std;
class A
{
public:
    A(int size) : size_(size)
    {
        data_ = new int[size];
    }
    A() {}
    A(const A &a)
    {
        size_ = a.size_;
        // data_ = a.data_;  // shallow copy
        data_ = new int[size_]; // deep copy
        cout << "copy " << endl;
    }

    A(A &&a)
    {
        this->data_ = a.data_;
        a.data_ = nullptr;
        cout << "move " << endl;
    }

    ~A()
    {
        if (data_ != nullptr)
        {
            delete[] data_;
        }
    }
    int *data_;
    int size_;
};
int main()
{
    A a(10);
    A b = a;
    A c = std::move(b); // 调用移动构造函数
    cout << "a " << a.data_ << endl;
    cout << "b " << b.data_ << endl;
    cout << "c " << a.data_ << endl;

    return 0;
}