#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *pattern = "^[a-zA-Z]+[0-9]*$"; // 正则表达式模式
    const char *text = "worLd789"; // 要匹配的文本

    regex_t regex;
    int result;

    // 编译正则表达式
    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result) {
        fprintf(stderr, "Could not compile regex: %s\n", pattern);
        exit(1);
    }

    // 匹配正则表达式
    result = regexec(&regex, text, 0, NULL, 0);
    if (!result) {
        printf("Match found: %s\n", text);
    } else if (result == REG_NOMATCH) {
        printf("No match found: %s\n", text);
    } else {
        char error_msg[256];
        regerror(result, &regex, error_msg, sizeof(error_msg));
        fprintf(stderr, "Regex match failed: %s\n", error_msg);
        exit(1);
    }

    // 释放正则表达式资源
    regfree(&regex);

    return 0;
}