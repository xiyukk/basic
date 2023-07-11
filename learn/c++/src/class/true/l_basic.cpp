// 引入必要的头文件
#include <iostream>
#include <string>
#if 0

/* 2.1 类的定义和简单用法
类是 C++ 中用于定义用户自定义类型的基本结构。类定义了一组数据成员和成员函数，
这些数据成员和成员函数共同组成了一个对象的状态和行为。 */

// 定义一个简单的类
class Dog {
public: // 公共访问修饰符，使得类的外部可以访问这些成员
// 成员变量
std::string name;
int age;

// 成员函数：输出狗的信息
void print_info() const {
    std::cout << "Name: " << name << ", Age: " << age << std::endl;
}
};

int main() {
    // 创建一个 Dog 类型的对象
    Dog dog1;

    // 设置对象的属性
    dog1.name = "Buddy";
    dog1.age = 3;

    // 调用对象的成员函数
    dog1.print_info();

    return 0;
}

#endif

#if 0
/* 2.2 构造函数和析构函数
构造函数用于初始化类的对象，当创建类的新实例时，它会自动被调用。析构函数在对象被销毁时自动调用，用于执行清理操作。 */
class Dog {
public:
// 构造函数：用于初始化对象
Dog(const std::string& dog_name, int dog_age)
: name(dog_name), age(dog_age) {
    std::cout << "Dog object created: " << name << std::endl;
}

// 析构函数：在对象被销毁时调用
~Dog() {
    std::cout << "Dog object destroyed: " << name << std::endl;
}

// 成员函数：输出狗的信息
void print_info() const {
    std::cout << "Name: " << name << ", Age: " << age << std::endl;
}

private: // 私有访问修饰符，使得类的外部无法访问这些成员
// 成员变量
std::string name;
int age;
};

int main() {
    // 使用构造函数创建对象，并初始化属性
    Dog dog1("Buddy", 3);
    dog1.print_info();

    // 当 main 函数结束时，dog1 的析构函数将被调用
    return 0;
}

#endif

#if 0
/* 2.3 访问控制
访问控制修饰符用于限制类成员的访问范围。有三种访问控制修饰符：public、protected 和 private。
它们分别表示公共访问、受保护访问和私有访问。 */

class Dog {
public:
// 公共成员：可以从类的外部访问
void print_info() const {
    std::cout << "Name: " << name << ", Age: " << age << std::endl;
}

protected:
// 受保护成员：只能在类内部、子类和友元函数中访问
int get_age() const {
    return age;
}

private:
// 私有成员：只能在类内部和友元函数中访问
std::string name;
int age;
};

#endif

#if 0
/* 2.4 继承
继承允许一个类从另一个类继承成员变量和成员函数。这有助于实现代码重用和多态性。
 */

// 基类
class Animal {
public:
Animal(const std::string& animal_name) : name(animal_name) {}

void print_name() const {
    std::cout << "Name: " << name << std::endl;
}

protected:
std::string name;
};

// 派生类
class Dog : public Animal {
public:
Dog(const std::string& dog_name, int dog_age)
: Animal(dog_name), age(dog_age) {}

void print_info() const {
    std::cout << "Name: " << name << ", Age: " << age << std::endl;
}

private:
int age;
};

int main() {
    Dog dog1("Buddy", 3);
    dog1.print_name(); // 调用基类的成员函数
    dog1.print_info(); // 调用派生类的成员函数

    return 0;
}

#endif

#if 1
/* 2.5 多态和虚函数
多态允许派生类的对象被当作基类的对象使用。为了实现多态，我们需要使用虚函数。
虚函数是在基类中声明的，它可以在派生类中被重写。 */

class Animal {
public:
virtual void speak() const { // 声明虚函数
    std::cout << "Animal speaks" << std::endl;
}
};

class Dog : public Animal {
public:
void speak() const override { // 重写虚函数
    std::cout << "Dog barks" << std::endl;
}
};

class Cat : public Animal {
public:
void speak() const override { // 重写虚函数
    std::cout << "Cat meows" << std::endl;
}
};

void make_animal_speak(const Animal& animal) {
    animal.speak();
}

int main() {
    Dog dog1;
    Cat cat1;

    make_animal_speak(dog1); // 输出 "Dog barks"
    make_animal_speak(cat1); // 输出 "Cat meows"

    return 0;
}

#endif