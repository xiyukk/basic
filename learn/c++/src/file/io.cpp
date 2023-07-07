#include <iostream>     // 用于标准输入输出流
#include <fstream>      // 用于文件输入输出流
#include <string>       // 用于处理字符串
#include <algorithm>    // 用于std::transform
#include <cctype>       // 用于std::toupper

int main() {
    // 打开输入文件
    std::ifstream infile("input.txt"); // 创建一个名为infile的输入文件流对象，并与文件input.txt进行关联
    if (!infile) {                     // 检查文件是否成功打开
        std::cerr << "无法打开输入文件。" << std::endl;
        return 1;
    }

    // 打开输出文件
    std::ofstream outfile("output.txt"); // 创建一个名为outfile的输出文件流对象，并与文件output.txt进行关联
    if (!outfile) {                      // 检查文件是否成功打开
        std::cerr << "无法打开输出文件。" << std::endl;
        return 2;
    }

    std::string line; // 用于存储每行文本的字符串
    while (std::getline(infile, line)) { // 使用std::getline从infile中读取一行文本，将其存储在line中
        // 将文本转换为大写
        std::transform(line.begin(), line.end(), line.begin(), ::tolower); // 使用std::transform将line中的所有字符转换为大写

        // 将转换后的文本写入输出文件
        outfile << line << std::endl; // 将转换后的line写入outfile，并添加换行符
    }

    // 关闭输入输出文件
    infile.close();  // 关闭输入文件流
    outfile.close(); // 关闭输出文件流

    return 0;
}