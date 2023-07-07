/* 
 * 可变长参数函数的应用
 */

#include <stdio.h>
#include <stdarg.h>

#if 0

/* 
 * 使用字符串作为模式来传递不同数据类型的参数
 */

typedef enum { INT, FLOAT, DOUBLE, CHAR } DataType;

void print_values(const char *pattern, ...);

int main() {
    print_values("idfc", 3, 8.0, 12.0f, 'A');
    return 0;
}

void print_values(const char *pattern, ...) {
    va_list args;
    va_start(args, pattern);

    // 遍历模式字符串
    for (const char *p = pattern; *p != '\0'; p++) {
        // 根据模式字符处理参数
        switch (*p) {
            case 'i': {
                int value = va_arg(args, int);
                printf("Integer: %d\n", value);
                break;
            }
            case 'd': {
                double value = va_arg(args, double);
                printf("Double: %.2f\n", value);
                break;
            }
            case 'f': {
                float value = va_arg(args, double);
                printf("Float: %.2f\n", value);
                break;
            }
            case 'c': {
                char value = va_arg(args, int); // 注意：字符参数会被提升为整数
                printf("Char: %c\n", value);
                break;
            }
            default:
                fprintf(stderr, "Invalid pattern: %c\n", *p);
                break;
        }
    }

    va_end(args);
}

#endif

#if 1
/* 
 * 使用枚举作为模式来传递不同数据类型的参数
 */

typedef enum { INT, FLOAT, DOUBLE, CHAR, END } DataType;

void print_values(DataType first, ...);

int main() {
    print_values(INT, 3, DOUBLE, 9.0, FLOAT, 12.0f, CHAR, 'A', END);
    return 0;
}

void print_values(DataType first, ...) {
    va_list args;
    va_start(args, first);

    DataType type = first;

    while (type != END) {
        switch (type) {
            case INT: {
                int value = va_arg(args, int);
                printf("Integer: %d\n", value);
                break;
            }
            case DOUBLE: {
                double value = va_arg(args, double);
                printf("Double: %.2f\n", value);
                break;
            }
            case FLOAT: {
                float value = va_arg(args, double);
                printf("Float: %.2f\n", value);
                break;
            }
            case CHAR: {
                char value = va_arg(args, int);
                printf("Char: %c\n", value);
                break;
            }
            default:
                fprintf(stderr, "Invalid data type\n");
                break;
        }

        type = va_arg(args, DataType);
    }

    va_end(args);
}
#endif