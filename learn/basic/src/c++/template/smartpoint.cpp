#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass(int value) : value_(value) {
        std::cout << "MyClass constructor: " << value_ << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass destructor: " << value_ << std::endl;
    }

    int getValue() const {
        return value_;
    }

private:
    int value_;
};

// 使用std::unique_ptr的函数
void use_unique_ptr() {
    std::unique_ptr<MyClass> ptr1(new MyClass(1)); // 创建std::unique_ptr

    // 使用make_unique创建std::unique_ptr（推荐）
    auto ptr2 = std::make_unique<MyClass>(2); 

    std::cout << "Value of ptr1: " << ptr1->getValue() << std::endl;
    std::cout << "Value of ptr2: " << ptr2->getValue() << std::endl;

    // 移动所有权
    std::unique_ptr<MyClass> ptr3 = std::move(ptr1);
    std::cout << "Value of ptr3: " << ptr3->getValue() << std::endl;

    // ptr1现在为空，不能解引用
    if (!ptr1) {
        std::cout << "ptr1 is empty" << std::endl;
    }
}

// 使用std::shared_ptr的函数
void use_shared_ptr() {
    std::shared_ptr<MyClass> ptr1(new MyClass(3)); // 创建std::shared_ptr

    // 使用make_shared创建std::shared_ptr（推荐）
    auto ptr2 = std::make_shared<MyClass>(4); 

    std::cout << "Value of ptr1: " << ptr1->getValue() << std::endl;
    std::cout << "Value of ptr2: " << ptr2->getValue() << std::endl;

    // 复制所有权
    std::shared_ptr<MyClass> ptr3 = ptr1;
    std::cout << "Value of ptr3: " << ptr3->getValue() << std::endl;

    std::cout << "ptr1 use count: " << ptr1.use_count() << std::endl;
    std::cout << "ptr2 use count: " << ptr2.use_count() << std::endl;
    std::cout << "ptr3 use count: " << ptr3.use_count() << std::endl;
}

// 使用std::weak_ptr的函数
void use_weak_ptr() {
    std::weak_ptr<MyClass> weak;

    {
        std::shared_ptr<MyClass> ptr = std::make_shared<MyClass>(5);
        weak = ptr; // 创建std::weak_ptr

        std::cout << "Value of ptr: " << ptr->getValue() << std::endl;
        std::cout << "ptr use count: " << ptr.use_count() << std::endl;
    }

    // 检查std::weak_ptr是否已过期
    if (weak.expired()) {
        std::cout << "weak_ptr is expired" << std::endl;
    }
}

int main() {
    std::cout << "=== unique_ptr ===" << std::endl;
    use_unique_ptr();

    std::cout << "=== shared_ptr ===" << std::endl;
    use_shared_ptr();

    std::cout << "=== weak_ptr ===" << std::endl;
    use_weak_ptr();

    return 0;
}