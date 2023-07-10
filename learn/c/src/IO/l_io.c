#include <stdio.h>
#include <stdlib.h>

#if 0
// 1. 标准输入输出
int main() {
    // 从标准输入（stdin）读取一个整数
    int input_number;
    printf("Enter an integer: ");
    scanf("%d", &input_number);

    // 将输入的整数打印到标准输出（stdout）
    printf("You entered: %d\n", input_number);

    // 如果输入的整数为负数，将错误信息输出到标准错误（stderr）
    if (input_number < 0) {
        fprintf(stderr, "Error: Negative number entered.\n");
    }

    return 0;
}
#endif


#if 0
// 2. 文件I/O - 打开、关闭、读取和写入文件

int main() {
    // 打开一个文件（如果不存在则创建）用于写入
    FILE *file = fopen("./src/IO/example.txt", "w");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // 向文件写入一些文本
    const char *text = "This is an example text.";
    fprintf(file, "%s\n", text);

    // 关闭文件
    fclose(file);

    // 重新打开文件以读取内容
    file = fopen("./src/IO/example.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // 读取文件内容并显示在屏幕上
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("Read from file: %s", buffer);
    }

    // 关闭文件
    fclose(file);

    return 0;
}
#endif

#if 0
// 3. 文件定位
int main() {
    // 打开一个文件用于读写
    FILE *file = fopen("./src/IO/example.txt", "r+");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // 定位到文件的第10个字节
    fseek(file, 10, SEEK_SET);

    // 写入一个字符
    fputc('X', file);

    // 定位到文件的倒数第5个字节
    fseek(file, -5, SEEK_END);

    // 写入一个字符
    fputc('Y', file);

    // 关闭文件
    fclose(file);

    return 0;
}
#endif

#if 1
// 4. 读取文件的大小
long get_file_size(FILE *file) {
    // 定位到文件末尾
    fseek(file, 0, SEEK_END);

    // 获取当前位置（字节）
    long size = ftell(file);

    // 重新定位到文件开头
    rewind(file);

    return size;
}

int main() {
    // 打开一个文件用于读取
    FILE *file = fopen("./src/IO/example.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // 获取文件的大小
    long file_size = get_file_size(file);
    printf("File size: %ld bytes\n", file_size);

    // 关闭文件
    fclose(file);

    return 0;
}
#endif
