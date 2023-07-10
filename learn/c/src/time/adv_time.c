#include <stdio.h>
#include <time.h>
#include <string.h>

#if 0
// 1. Custom time formatting with strftime
// 使用 strftime 自定义时间格式
int main() {
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);

    // Format time using custom format specifiers
    char buffer[80];
    strftime(buffer, sizeof(buffer), "Today is %A, %B %d, %Y. Time: %I:%M %p", local_time);
    printf("Custom formatted time: %s\n", buffer);

    return 0;
}
#endif

#if 0
// 2. Parsing time strings with strptime
//    使用 strptime 解析时间字符串

int main() {
    const char *time_string = "2023-07-28 14:30:00";
    struct tm parsed_time;
    memset(&parsed_time, 0, sizeof(parsed_time));

    // Parse the time string using strptime
    char *result = strptime(time_string, "%Y-%m-%d %H:%M:%S", &parsed_time);
    if (result) {
        printf("Parsed time: %d-%02d-%02d %02d:%02d:%02d\n",
               parsed_time.tm_year + 1900, parsed_time.tm_mon + 1, parsed_time.tm_mday,
               parsed_time.tm_hour, parsed_time.tm_min, parsed_time.tm_sec);
    } else {
        printf("Failed to parse time string.\n");
    }

    return 0;
}
#endif


#if 0
// 3. Converting between time zones
// 在时区之间转换
int main() {
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);

    // Display local time
    char local_buffer[80];
    strftime(local_buffer, sizeof(local_buffer), "%Y-%m-%d %H:%M:%S %Z", local_time);
    printf("Local time: %s\n", local_buffer);

    // Convert local time to UTC
    struct tm *utc_time = gmtime(&current_time);
    char utc_buffer[80];
    strftime(utc_buffer, sizeof(utc_buffer), "%Y-%m-%d %H:%M:%S %Z", utc_time);
    printf("UTC time: %s\n", utc_buffer);

    return 0;
}
#endif

#if 1
// 4. Using difftime to compare time points
// 使用差分时间比较时间点
int main() {
    struct tm time1, time2;

    // Set time1 to 2023-07-10 10:30:00
    time1.tm_year = 2023 - 1900;
    time1.tm_mon = 7 - 1;
    time1.tm_mday = 10;
    time1.tm_hour = 10;
    time1.tm_min = 30;
    time1.tm_sec = 0;
    time1.tm_isdst = -1;

    // Set time2 to 2023-07-10 11:45:00
    time2.tm_year = 2023 - 1900;
    time2.tm_mon = 7 - 1;
    time2.tm_mday = 10;
    time2.tm_hour = 11;
    time2.tm_min = 45;
    time2.tm_sec = 0;
    time2.tm_isdst = -1;

    // Calculate the time difference
    time_t time1_t = mktime(&time1);
    time_t time2_t = mktime(&time2);
    double time_diff = difftime(time2_t, time1_t);

    printf("Time difference: %.0lf min\n", time_diff / 60);

    return 0;
}
#endif