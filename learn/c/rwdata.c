#include <stdio.h>
#include <stdlib.h>

#define MAX_FILENAME_LENGTH 256

/* 

这段程序主要实现了文件操作的功能。以下是每个系统函数的作用：
1. fopen：打开文件并返回文件指针，如果失败则返回 NULL。
2. perror：输出错误信息到标准错误流。
3. fclose：关闭文件。
4. fseek：移动文件指针到指定位置。
5. ftell：获取当前文件指针的位置。
6. rewind：将文件指针移动到文件开头。
7. feof：检查是否已到达文件结尾。
8. fread：从文件中读取数据。
9. ferror：检查文件操作是否发生错误。
10. fwrite：向文件中写入数据。
11. fprintf：格式化输出到文件。
12. getline：从文件中读取一行文本。
13. fscanf：从文件中读取格式化数据。
14. strlen：计算字符串的长度。
15. fgets：从标准输入中读取一行文本。

 */

long copy_file(const char *src_filename, const char *dest_filename)
{
    // 打开源文件
    FILE *src_file = fopen(src_filename, "rb");
    if (src_file == NULL)
    {
        // 处理打开文件失败的情况，并输出错误信息
        perror("fopen failed for source file");
        return -1;
    }

    // 打开目标文件
    FILE *dest_file = fopen(dest_filename, "wb");
    if (dest_file == NULL)
    {
        // 处理打开文件失败的情况，并输出错误信息
        perror("fopen failed for destination file");
        fclose(src_file);
        return -1;
    }

    // 获取源文件大小并移动文件指针到开头
    // 从文件末尾向前偏移0的长度给文件指针fp
    fseek(src_file, 0, SEEK_END);
    long file_size = ftell(src_file);
    rewind(src_file);

    char buffer[1024];
    long total_bytes_written = 0;
    while (!feof(src_file))
    {
        // 从源文件中读取数据
        int bytes_read = fread(buffer, 1, sizeof(buffer), src_file);
        if (ferror(src_file))
        {
            // 处理读取文件失败的情况，并输出错误信息
            perror("error reading from source file");
            fclose(src_file);
            fclose(dest_file);
            return -1;
        }
        // 将读取的数据写入目标文件
        int bytes_written = fwrite(buffer, 1, bytes_read, dest_file);
        if (ferror(dest_file))
        {
            // 处理写入文件失败的情况，并输出错误信息
            perror("error writing to destination file");
            fclose(src_file);
            fclose(dest_file);
            return -1;
        }
        // 统计已成功写入的字节数
        total_bytes_written += bytes_written;
    }

    // 关闭文件并返回总共写入的字节数
    fclose(src_file);
    fclose(dest_file);
    return total_bytes_written;
}
char *read_line(FILE *file)
{
    char *line = NULL;
    size_t line_size = 0;
    ssize_t bytes_read = getline(&line, &line_size, file);
    if (bytes_read == -1)
    {
        // 处理读取文件失败的情况，并输出错误信息
        perror("getline failed");
        free(line);
        return NULL;
    }
    if (line[bytes_read - 1] == '\n')
    {
        // 如果读取到换行符，则将其替换成字符串结束符
        line[bytes_read - 1] = '\0';
    }
    return line;
}
int read_int(FILE *file)
{
    int value;
    int bytes_read = fscanf(file, "%d", &value);
    if (bytes_read != 1)
    {
        // 处理读取文件失败的情况，并输出错误信息
        perror("fscanf failed");
        return -1;
    }
    return value;
}
int write_int(FILE *file, int value)
{
    // 将整数格式化并写入文件
    int bytes_written = fprintf(file, "%d\n", value);
    if (bytes_written < 0)
    {
        // 处理向文件写入数据失败的情况，并输出错误信息
        perror("fprintf failed");
        return -1;
    }
    return bytes_written;
}

int main()
{
    char *src_filename = "../pic/R-C.jpeg";
    char *dest_filename = "../pic/123.png";
    char *dst_filename = "../pic/text.json";

    // 调用函数将源文件复制到目标文件
    long bytes_copied = copy_file(src_filename, dest_filename);
    if (bytes_copied == -1)
    {
        printf("File copy failed\n");
        return 1;
    }
    else
    {
        printf("%ld bytes copied\n", bytes_copied);
    }

    // 打开目标文件并读取用户输入的整数，然后将其写入文件
    FILE *dest_file = fopen(dst_filename, "r+");
    if (dest_file == NULL)
    {
        // 处理打开文件失败的情况，并输出错误信息
        perror("fopen failed for destination file");
        return 1;
    }

    printf("Enter an integer to write to the file: ");
    int value = read_int(stdin);
    if (value == -1)
    {
        printf("Failed to read integer from input\n");
        fclose(dest_file);
        return 1;
    }

    int bytes_written = write_int(dest_file, value);
    if (bytes_written == -1)
    {
        printf("Failed to write integer to file\n");
        fclose(dest_file);
        return 1;
    }
    else
    {
        printf("%d bytes written to file\n", bytes_written);
    }

    // 将文件指针移动到文件开头，并逐行读取文件内容并输出到控制台
    rewind(dest_file);

    printf("Contents of destination file:\n");
    char *line;
    while ((line = read_line(dest_file)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    if (!feof(dest_file))
    {
        // 处理读取文件失败的情况，并输出错误信息
        perror("error reading from destination file");
        fclose(dest_file);
        return 1;
    }

    // 关闭文件并退出程序
    fclose(dest_file);
    return 0;
}
