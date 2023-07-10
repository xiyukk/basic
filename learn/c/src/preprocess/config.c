#include <stdio.h>
#include "config.h"

/* 
 * 在这个示例中，我们定义了两个宏ENABLE_FEATURE_A和ENABLE_FEATURE_B，它们分别表示功能A和功能B是否启用。
 * 在config.c中，我们使用预处理器的#if指令检查这些宏的值，根据配置执行相应的代码。
 * 要启用功能B或禁用功能A，你可以在编译时通过-D选项定义宏：
 * # 启用功能B，禁用功能A
 * gcc main.c -o program -DENABLE_FEATURE_A=0 -DENABLE_FEATURE_B=1
 * 运行程序：./program
 */

#if ENABLE_FEATURE_A
void feature_a() {
    printf("Feature A is enabled.\n");
}
#else
void feature_a() {
    printf("Feature A is disabled.\n");
}
#endif

#if ENABLE_FEATURE_B
void feature_b() {
    printf("Feature B is enabled.\n");
}
#else
void feature_b() {
    printf("Feature B is disabled.\n");
}
#endif

int main() {
    feature_a();
    feature_b();
    return 0;
}