#include <stdio.h>
#include <stdlib.h>

#define MAX_FILENAME_LENGTH 256

// 从源文件中读取数据并将其写入目标文件。返回成功写入的字节数，如果出错则返回 -1。
long copy_file(const char *src_filename, const char *dest_filename)
{
    FILE *src_file = fopen(src_filename, "rb");
    if (src_file == NULL)
    {
        perror("fopen failed for source file");
        return -1;
    }

    FILE *dest_file = fopen(dest_filename, "wb");
    if (dest_file == NULL)
    {
        perror("fopen failed for destination file");
        fclose(src_file);
        return -1;
    }

    fseek(src_file, 0, SEEK_END);
    long file_size = ftell(src_file);
    rewind(src_file);

    char buffer[1024];
    long total_bytes_written = 0;
    while (!feof(src_file))
    {
        int bytes_read = fread(buffer, 1, sizeof(buffer), src_file);
        if (ferror(src_file))
        {
            perror("error reading from source file");
            fclose(src_file);
            fclose(dest_file);
            return -1;
        }
        int bytes_written = fwrite(buffer, 1, bytes_read, dest_file);
        if (ferror(dest_file))
        {
            perror("error writing to destination file");
            fclose(src_file);
            fclose(dest_file);
            return -1;
        }
        total_bytes_written += bytes_written;
    }

    fclose(src_file);
    fclose(dest_file);
    return total_bytes_written;
}

// 从文件中读取一个字符串，直到遇到换行符或文件末尾。返回读取的字符串，或者 NULL 如果出错。
char *read_line(FILE *file)
{
    char *line = NULL;
    size_t line_size = 0;
    size_t bytes_read = getline(&line, &line_size, file);
    if (bytes_read == -1)
    {
        perror("getline failed");
        free(line);
        return NULL;
    }
    if (line[bytes_read - 1] == '\n')
    {
        line[bytes_read - 1] = '\0';
    }
    return line;
}

// 从文件中读取一个整数。返回读取的整数，或者 -1 如果出错。
int read_int(FILE *file)
{
    int value;
    int bytes_read = fscanf(file, "%d", &value);
    if (bytes_read != 1)
    {
        perror("fscanf failed");
        return -1;
    }
    return value;
}

// 将一个整数写入文件。返回成功写入的字节数，或者 -1 如果出错。
int write_int(FILE *file, int value)
{
    int bytes_written = fprintf(file, "%d\n", value);
    if (bytes_written < 0)
    {
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

    /* printf("Enter source filename: ");
    fflush(stdout); // 在没有换行符的情况下清空输出缓冲区
    if (fgets(src_filename, sizeof(src_filename), stdin) == NULL)
    {
        perror("fgets failed");
        return 1;
    }
    if (src_filename[strlen(src_filename) - 1] == '\n')
    {
        src_filename[strlen(src_filename) - 1] = '\0';
    }

    printf("Enter destination filename: ");
    fflush(stdout);
    if (fgets(dest_filename, sizeof(dest_filename), stdin) == NULL)
    {
        perror("fgets failed");
        return 1;
    }
    if (dest_filename[strlen(dest_filename) - 1] == '\n')
    {
        dest_filename[strlen(dest_filename) - 1] = '\0';
    } */

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

    FILE *dest_file = fopen(dst_filename, "r+");
    if (dest_file == NULL)
    {
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
        perror("error reading from destination file");
        fclose(dest_file);
        return 1;
    }

    fclose(dest_file);
    return 0;
}