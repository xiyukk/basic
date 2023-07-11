#include <stdio.h>
#include <unistd.h>
#include <string.h>
/* 1. 命令行参数基础
在C语言中，程序的入口函数main()接受两个参数：int argc 和 char *argv[] 。argc表示命令行参数的数量，argv是一个字符串数组，其中包含每个参数。argv[0]通常是程序的名称。
以下是一个简单的示例，它打印出所有命令行参数： */

#if 0
int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    return 0;
}
#endif


/* 2. 使用getopt()解析选项
    getopt()是一个用于解析命令行选项的库函数。它可以解析短选项（如-a）和长选项（如--all）。
    以下是一个使用getopt()解析命令行选项的示例：
    该程序接受两个选项：-a（无参数）和-b（带一个参数）。
    getopt()函数会自动处理这些选项并将它们的值存储在相应的变量中。
 */

#if 1
int main(int argc, char *argv[]) {
    int opt;
    int flag_a = 0;
    int flag_b = 0;
    char *arg_b = NULL;

    while ((opt = getopt(argc, argv, "ab:")) != -1) {
        switch (opt) {
            case 'a':
                flag_a = 1;
                break;
            case 'b':
                flag_b = 1;
                arg_b = optarg;
                break;
            default:
                printf("Usage: %s [-a] [-b arg]\n", argv[0]);
                return 1;
        }
    }

    printf("Option 'a': %s\n", flag_a ? "enabled" : "disabled");
    if (flag_b) {
        printf("Option 'b': enabled with argument '%s'\n", arg_b);
    } else {
        printf("Option 'b': disabled\n");
    }

    return 0;
}
#endif

