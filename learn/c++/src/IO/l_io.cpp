#if 1
#include <iostream>

int main() {
    int num;

    // 从控制台读取一个整数
    std::cout << "Enter a number: ";
    std::cin >> num;

    // 输出整数到控制台
    std::cout << "The number you entered is: " << num << std::endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // 打开输入文件
    std::ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    // 打开输出文件
    std::ofstream output_file("output.txt");
    if (!output_file.is_open()) {
        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(input_file, line)) {
        // 将输入文件的每一行写入输出文件
        output_file << line << std::endl;
    }

    // 关闭文件
    input_file.close();
    output_file.close();

    return 0;
}
#endif

#if 0
/* I/O操作符重载
C++允许我们重载输入和输出操作符，以便为自定义类型提供更简洁和直观的I/O操作。
下面是一个示例，向我们展示如何为一个简单的 Point 类重载 << 和 >> 操作符：
在这个示例中，我们重载了 << 和 >> 操作符，以便将 Point 对象以更友好的格式输出到控制台，
并从控制台读取 Point 对象的数据。我们使用了 friend 关键字，使这些重载函数可以访问 Point 类的私有成员。 */
#include <iostream>

class Point {
public:
Point(int x = 0, int y = 0) : x(x), y(y) {}

// 重载输出操作符<<
friend std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

// 重载输入操作符>>
friend std::istream& operator>>(std::istream& is, Point& point) {
    // 从输入流读取两个整数，用逗号分隔，并存储到Point对象的成员变量中
    char comma;
    is >> point.x >> comma >> point.y;
    return is;
}

private:
int x, y;
};

int main() {
    Point p1, p2;

    // 读取用户输入的两个点
    std::cout << "Enter the coordinates of two points (x, y): ";
    std::cin >> p1 >> p2;

    // 输出两个点的坐标
    std::cout << "The coordinates of the points are: " << p1 << " and " << p2 << std::endl;

    return 0;
}

#endif

#if 0
/* I/O流操纵器用于修改I/O流的格式和行为。这些操纵器可以与 cin 和 cout 一起使用，以更改输入或输出的格式。
在这个示例中，我们使用了 std::fixed 和 std::setprecision() 操纵器来设置输出浮点数的精度，
以及 std::setw() 和 std::setfill() 操纵器来设置输出宽度和填充字符。 
*/

#include <iostream>
#include <iomanip>

int main() {
    double pi = 3.14159265358979323846;

    // 设置输出的浮点数精度
    std::cout << std::fixed << std::setprecision(2)
        << "Pi with 2 decimal places: " << pi << std::endl;

    // 设置输出宽度和填充字符
    std::cout << std::setw(10) << std::setfill('-') << pi << std::endl;

    return 0;
}

#endif

#if 0
// 二进制文件I/O用于以二进制格式读取和写入数据。这对于处理非文本文件（如图像、音频、视频等）特别有用。以下是一个简单的示例，展示了如何使用二进制I/O模式复制一个文件：
#include <iostream>
#include <fstream>

int main() {
    // 以二进制模式打开输入文件
    std::ifstream input_file("input.bin", std::ios::binary);
    if (!input_file.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    // 以二进制模式打开输出文件
    std::ofstream output_file("output.bin", std::ios::binary);
    if (!output_file.is_open()) {
        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }

    // 复制文件
    output_file << input_file.rdbuf();

    // 关闭文件
    input_file.close();
    output_file.close();

    return 0;
}
#endif

#if 0
// 字符串流（std::stringstream）允许您将字符串视为I/O流，从而可以对字符串执行类似于文件I/O操作的操作。以下是一个示例，演示了如何使用std::stringstream解析一个逗号分隔的字符串：

#include <iostream>
#include <sstream>
#include <vector>

int main() {
    std::string input = "1,2,3,4,5";
    std::stringstream ss(input);
    std::vector<int> numbers;
    int num;
    char comma;

    // 从字符串流中读取整数和逗号
    while (ss >> num >> comma) {
        numbers.push_back(num);
    }

    // 输出解析后的整数
    std::cout << "Parsed numbers:" << std::endl;
    for (const auto& n : numbers) {
        std::cout << n << std::endl;
    }

    return 0;
}

#endif

#if 0
/* 自定义流缓冲区
自定义流缓冲区允许您控制流如何读取和写入数据。以下是一个简单的示例，演示了如何为输出流创建一个自定义缓冲区，
以便在每次输出换行符时自动添加行号：

在这个示例中，我们创建了一个名为LineNumberBuffer的自定义流缓冲区类，该类从std::streambuf派生。
我们重载了overflow()函数，以便在每次输出换行符时添加行号。然后，我们使用自定义流缓冲区包装std::cout的缓冲区，
并将其连接到一个新的输出流numbered_output，以便使用该自定义流缓冲区输出文本。 */

#include <iostream>
#include <streambuf>
#include <ostream>

class LineNumberBuffer : public std::streambuf {
public:
LineNumberBuffer(std::streambuf* buf) : wrapped_buf(buf), line_number(1) {}

protected:
// 重载溢出函数，以便在每次输出换行符时添加行号
virtual int_type overflow(int_type c) {
    if (c == '\n') {
        char line_number_str[32];
        std::sprintf(line_number_str, "%d: ", ++line_number);
        wrapped_buf->sputn(line_number_str, std::strlen(line_number_str));
    }
    return wrapped_buf->sputc(c);
}

private:
std::streambuf* wrapped_buf;
int line_number;
};

int main() {
    LineNumberBuffer lnb(std::cout.rdbuf());
    std::ostream numbered_output(&lnb);

    // 使用自定义输出流输出文本
    numbered_output << "Line 1\nLine 2\nLine 3\n";

    return 0;
}
#endif

#if 0
/* 使用std::ifstream（输入文件流）和std::ofstream（输出文件流）来读写文本文件。
在这个示例中，我们创建了一个名为input_file的std::ifstream对象，并将其与名为input.txt的文本文件关联。然后，我们使用std::getline()函数从文件中逐行读取文本，并将其输出到控制台。最后，我们关闭文件。
 */

#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(input_file, line)) {
        std::cout << line << std::endl;
    }

    input_file.close();
    return 0;
}
#endif

#if 0
/* 写入文本文件
在这个示例中，我们创建了一个名为output_file的std::ofstream对象，并将其与名为output.txt的文本文件关联。然后，我们将字符串"Hello, World!"写入文件。最后，我们关闭文件。
 */

#include <iostream>
#include <fstream>

int main() {
    std::ofstream output_file("output.txt");
    if (!output_file.is_open()) {
        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }

    output_file << "Hello, World!" << std::endl;
    output_file.close();

    return 0;
}
#endif

#if 0
/* 创建一个自定义输入流缓冲区，该缓冲区将从用户输入中删除空格：

在这个示例中，我们创建了一个名为NoSpaceBuffer的自定义输入流缓冲区类，该类从std::streambuf派生。我们重载了uflow()函数，以便从用户输入中删除空格。然后，我们将自定义输入流缓冲区与std::cin的缓冲区关联，并创建了一个名为no_space_input的新输入流对象。我们使用这个新输入流对象从用户输入中读取字符串，但在输出时不包含空格。
请注意，这个示例可能不适用于所有情况，因为它只处理了空格字符。根据需要，您可以修改NoSpaceBuffer类以处理其他类型的字符。 */

#include <iostream>
#include <streambuf>
#include <istream>

class NoSpaceBuffer : public std::streambuf {
public:
NoSpaceBuffer(std::streambuf* buf) : wrapped_buf(buf) {}

protected:
// 重载uflow()函数，以便从用户输入中删除空格
virtual int_type uflow() {
    int_type c;
    do {
        c = wrapped_buf->sbumpc();
    } while (c == ' ');

    return c;
}

private:
std::streambuf* wrapped_buf;
};

int main() {
    NoSpaceBuffer nsb(std::cin.rdbuf());
    std::istream no_space_input(&nsb);

    std::string input;
    std::cout << "Enter a string with spaces: ";
    std::getline(no_space_input, input);

    std::cout << "String without spaces: " << input << std::endl;
    return 0;
}

#endif

#if 0

#endif