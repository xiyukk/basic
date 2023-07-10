#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 5

#if 0
// 1. 二进制文件读写
typedef struct {
    int id;
    char name[50];
    float salary;
} Employee;

int main() {
    Employee employees[3] = {
        {1, "Alice", 50000.0},
        {2, "Bob", 60000.0},
        {3, "Charlie", 55000.0}
    };

    // 以二进制写模式打开文件
    FILE *file = fopen("./src/IO/employees.bin", "wb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // 写入结构体数组到文件
    fwrite(employees, sizeof(Employee), 3, file);
    fclose(file);

    // 以二进制读模式打开文件
    file = fopen("./src/IO/employees.bin", "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    Employee read_employees[3];
    // 从文件中读取结构体数组
    fread(read_employees, sizeof(Employee), 3, file);
    fclose(file);

    // 打印读取到的结构体数组
    for (int i = 0; i < 3; i++) {
        printf("Employee ID: %d, Name: %s, Salary: %.2f\n",
               read_employees[i].id, read_employees[i].name, read_employees[i].salary);
    }

    return 0;
}
#endif


#if 0
// 2. 使用tmpfile创建临时文件
int main() {
    // 创建一个临时文件
    FILE *temp_file = tmpfile();
    if (!temp_file) {
        perror("Error creating temp file");
        return 1;
    }

    // 向临时文件写入数据
    fputs("Hello, this is a temporary file!", temp_file);

    // 将文件指针定位到文件开头
    rewind(temp_file);

    // 从临时文件读取数据并显示在屏幕上
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), temp_file) != NULL) {
        printf("Read from temp file: %s\n", buffer);
    }

    // 关闭临时文件，临时文件将自动删除
    fclose(temp_file);

    return 0;
}
#endif 

#if 0
// 3. 使用setvbuf设置文件缓冲模式
int main() {
    // 以写模式打开文件
    FILE *file = fopen("./src/IO/sexample.txt", "w");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // 设置文件为无缓冲模式
    setvbuf(file, NULL, _IONBF, 0);

    // 向文件写入数据
    fputs("Hello, this file is unbuffered!", file);

    // 关闭文件
    fclose(file);

    return 0;
}
#endif


#if 1
// 4. 使用flockfile和funlockfile对文件加锁
FILE *file;
void *write_to_file(void *arg) {
    // 对文件加锁
    flockfile(file);

    // 向文件写入数据
    fprintf(file, "Thread %ld is writing to the file.\n", (long)arg);

    // 对文件解锁
    funlockfile(file);

    return NULL;
}

int main() {
    // 以写模式打开文件
    file = fopen("./src/IO/lock_example.txt", "w");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // 创建多个线程并让它们向文件写入数据
    pthread_t threads[THREAD_COUNT];
    for (long i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, write_to_file, (void *)i);
    }

    // 等待所有线程完成
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    // 关闭文件
    fclose(file);

    return 0;
}
#endif