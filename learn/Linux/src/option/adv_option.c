#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


/* 3. 高级用法：子命令和参数验证
对于复杂的命令行程序，您可能希望使用子命令（如git commit、git push等）。在这种情况下，您可以使用getopt()解析全局选项，然后根据子命令继续解析特定选项。
以下示例展示了如何处理子命令和参数验证： */

#if 0
/* 
$ ./adv_option -a add -x "argument for x" -y "argument for y"
Global option a
add option x with argument: argument for x
add option y with argument: argument for y

$ ./adv_option -b "global arg" remove -z
Global option b with argument: global arg
remove option z
此示例在全局选项解析后检查子命令并分别解析它们的选项。您还可以在此添加参数验证以确保用户提供了正确的选项和参数值。
*/


// 打印程序用法
void print_usage(char *prog_name) {
    printf("Usage:\n");
    printf("  %s global [-a] [-b arg] command [options]\n", prog_name);
    printf("Commands:\n");
    printf("  add [-x arg] [-y arg]\n");
    printf("  remove [-z]\n");
}

int main(int argc, char *argv[]) {
    int opt;

    // 解析全局选项
    while ((opt = getopt(argc, argv, "ab:")) != -1) {
        switch (opt) {
            case 'a': // 处理全局选项 -a
                printf("Global option a\n");
                break;
            case 'b': // 处理全局选项 -b，并获取选项参数
                printf("Global option b with argument: %s\n", optarg);
                break;
            default: // 未知选项
                print_usage(argv[0]);
                return 1;
        }
    }

    // 检查子命令
    if (optind < argc) {
        char *command = argv[optind];
        optind++;

        if (strcmp(command, "add") == 0) {
            // 解析 "add" 子命令选项
            opt = 0; // 重置 opt
            while ((opt = getopt(argc, argv, "x:y:")) != -1) {
                switch (opt) {
                    case 'x': // 处理子命令 add 的选项 -x，并获取选项参数
                        printf("add option x with argument: %s\n", optarg);
                        break;
                    case 'y': // 处理子命令 add 的选项 -y，并获取选项参数
                        printf("add option y with argument: %s\n", optarg);
                        break;
                    default: // 未知选项
                        print_usage(argv[0]);
                        return 1;
                }
            }
        } else if (strcmp(command, "remove") == 0) {
            // 解析 "remove" 子命令选项
            opt = 0; // 重置 opt
            while ((opt = getopt(argc, argv, "z")) != -1) {
                switch (opt) {
                    case 'z': // 处理子命令 remove 的选项 -z
                        printf("remove option z\n");
                        break;
                    default: // 未知选项
                        print_usage(argv[0]);
                        return 1;
                }
            }
        } else {
            // 未知子命令
            fprintf(stderr, "Unknown command: %s\n", command);
            print_usage(argv[0]);
            return 1;
        }
    } else {
        // 没有指定子命令
        fprintf(stderr, "No command specified\n");
        print_usage(argv[0]);
        return 1;
    }

    // 参数验证和程序逻辑
    // 在这里添加针对每个子命令的逻辑。例如，你可以根据选项和参数执行特定的操作。
    // 请注意，为了简洁起见，示例代码中省略了大量错误处理和参数验证。

    return 0;
}
#endif


#if 0 

/* 
$ ./adv_option -a -b 10 add -x 5 -y 6
全局选项 a
全局选项 b，参数：10
加法结果：11

$ ./adv_option -a -b 10 remove -z 3
全局选项 a
全局选项 b，参数：10
移除结果（从全局 -b 参数减去 z）：7
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 打印程序用法
void print_usage(char *prog_name) {
    printf("用法：\n");
    printf("  %s global [-a] [-b arg] command [options]\n", prog_name);
    printf("命令：\n");
    printf("  add -x num1 -y num2\n");
    printf("  remove -z num2\n");
}

int main(int argc, char *argv[]) {
    int opt;
    int x = 0, y = 0, z = 0;
    int b_value = 0; // 保存全局 -b 参数的值

    // 解析全局选项
    while ((opt = getopt(argc, argv, "ab:")) != -1) {
        switch (opt) {
            case 'a':
                printf("全局选项 a\n");
                break;
            case 'b':
                printf("全局选项 b，参数：%s\n", optarg);
                b_value = atoi(optarg); // 保存 -b 参数的值
                break;
            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    // 检查子命令
    if (optind < argc) {
        char *command = argv[optind];
        optind++;

        if (strcmp(command, "add") == 0) {
            // 解析 "add" 子命令选项
            while ((opt = getopt(argc, argv, "x:y:")) != -1) {
                switch (opt) {
                    case 'x':
                        x = atoi(optarg);
                        break;
                    case 'y':
                        y = atoi(optarg);
                        break;
                    default:
                        print_usage(argv[0]);
                        return 1;
                }
            }
            // "add" 子命令逻辑
            printf("加法结果：%d\n", x + y);
        } else if (strcmp(command, "remove") == 0) {
            // 解析 "remove" 子命令选项
            while ((opt = getopt(argc, argv, "z:")) != -1) {
                switch (opt) {
                    case 'z':
                        z = atoi(optarg);
                        break;
                    default:
                        print_usage(argv[0]);
                        return 1;
                }
            }
            // "remove" 子命令逻辑
            printf("移除结果（从全局 -b 参数减去 z）：%d\n", b_value - z);
        } else {
            fprintf(stderr, "未知命令：%s\n", command);
            print_usage(argv[0]);
            return 1;
        }
    } else {
        fprintf(stderr, "未指定命令\n");
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}
#endif


#if 1
/* 
4. 复杂用法
 * $ gcc task_manager.c -o task_manager
 * $ ./task_manager add "Buy groceries"
 * $ ./task_manager add "Do laundry"
   $ ./task_manager list
   1: Buy groceries
   2: Do laundry
    $ ./task_manager remove 1
$ ./task_manager list
1: Do laundry
 */

#define TASK_FILE "./src/option/tasks.txt"

void print_usage(char *prog_name) {
    printf("Usage:\n");
    printf("  %s command [options]\n", prog_name);
    printf("Commands:\n");
    printf("  add <task>\n");
    printf("  remove <task_id>\n");
    printf("  list\n");
}

int add_task(const char *task) {
    FILE *file = fopen(TASK_FILE, "a");
    if (!file) {
        perror("Error opening task file");
        return 1;
    }

    fprintf(file, "%s\n", task);
    fclose(file);
    return 0;
}

int remove_task(int task_id) {
    FILE *file = fopen(TASK_FILE, "r");
    if (!file) {
        perror("Error opening task file");
        return 1;
    }

    FILE *temp = tmpfile();
    if (!temp) {
        perror("Error creating temporary file");
        fclose(file);
        return 1;
    }

    int line_no = 1;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (line_no != task_id) {
            fputs(buffer, temp);
        }
        line_no++;
    }

    fclose(file);

    file = fopen(TASK_FILE, "w");
    if (!file) {
        perror("Error opening task file");
        return 1;
    }

    rewind(temp);
    while (fgets(buffer, sizeof(buffer), temp)) {
        fputs(buffer, file);
    }

    fclose(file);
    fclose(temp);
    return 0;
}

int list_tasks() {
    FILE *file = fopen(TASK_FILE, "r");
    if (!file) {
        perror("Error opening task file");
        return 1;
    }

    int task_id = 1;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%d: %s", task_id, buffer);
        task_id++;
    }

    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "No command specified\n");
        print_usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "add") == 0) {
        if (argc < 3) {
            fprintf(stderr, "No task specified\n");
            print_usage(argv[0]);
            return 1;
        }

        return add_task(argv[2]);
    } else if (strcmp(argv[1], "remove") == 0) {
        if (argc < 3) {
            fprintf(stderr, "No task ID specified\n");
            print_usage(argv[0]);
            return 1;
        }

        int task_id = atoi(argv[2]);
        return remove_task(task_id);
    } else if (strcmp(argv[1], "list") == 0) {
        return list_tasks();
    } else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}
#endif