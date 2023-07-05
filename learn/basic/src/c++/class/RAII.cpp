#include <iostream>
#include <fstream>
#include <string>

/* 
* RAII（Resource Acquisition Is Initialization，资源获取即初始化）是一种C++编程技术，
* 用于管理资源的生命周期，如内存、文件句柄、线程和互斥锁等。
* RAII通过将资源的管理与对象的生命周期绑定来确保资源的正确释放。当对象创建时，资源被分配；当对象销毁时，资源被释放。
 */


// 定义一个RAII类，用于管理文件资源
class File {
public:
    // 构造函数，打开文件
    explicit File(const std::string& filename)
        : file_(filename, std::ios::in) {
        if (!file_.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        std::cout << "File opened: " << filename << std::endl;
    }

    // 析构函数，关闭文件
    ~File() {
        file_.close();
        std::cout << "File closed." << std::endl;
    }

    // 读取文件的一行
    std::string read_line() {
        std::string line;
        if (std::getline(file_, line)) {
            return line;
        }
        return "";
    }

private:
    std::ifstream file_;
};

int main() {
    try {
        // 创建File对象，打开文件
        File file("example.txt");

        // 读取并输出文件的内容
        std::string line;
        while (!(line = file.read_line()).empty()) {
            std::cout << "Line: " << line << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    // File对象超出作用域，资源被自动释放
    return 0;
}