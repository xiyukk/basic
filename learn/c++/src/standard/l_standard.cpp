#if 1

#include <iostream>
#include <iomanip>
#include <sstream>

int main() {
    int age = 30;
    double height = 1.75;
    std::string name = "John Doe";

    // 创建一个stringstream对象
    std::stringstream ss;

    // 使用流操作符和格式化操作设置输出格式
    ss << "Name: " << std::setw(10) << std::left << name
       << " Age: " << std::setw(3) << std::right << age
       << " Height: " << std::fixed << std::setprecision(2) << height << "m";

    // 将格式化后的输出转换为字符串
    std::string formatted_output = ss.str();

    // 打印格式化后的输出
    std::cout << formatted_output << std::endl;

    return 0;
}
#endif
