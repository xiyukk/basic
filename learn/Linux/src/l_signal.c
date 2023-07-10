#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#if 0
/* 
 * 运行程序后，通过按下Ctrl+C或在另一个终端中使用kill命令发送SIGTERM信号来观察程序如何响应信号。
 */

// 信号处理函数，接收一个整数型的信号编号
void signal_handler(int signum) {
    printf("收到信号 %d\n", signum);
}

int main() {
    // 注册信号处理函数
    // 当接收到SIGINT（通常是通过按下Ctrl+C触发）时，调用signal_handler函数
    signal(SIGINT, signal_handler);

    // 注册信号处理函数
    // 当接收到SIGTERM（通常是通过kill命令触发）时，调用signal_handler函数
    signal(SIGTERM, signal_handler);

    // 无限循环，等待信号触发
    while (1) {
        printf("等待信号...\n");
        sleep(1);
    }

    return 0;
}

#endif

# if 0
// 信号处理函数，接收一个整数型的信号编号
void sigstop(int signum) {
    printf("收到信号 %d\n", signum);

    // 根据不同信号采取相应的处理措施
    switch (signum) {
        case SIGINT:
            printf("SIGINT: 中断\n");
            break;
        case SIGQUIT:
            printf("SIGQUIT: 退出\n");
            exit(0);
            break;
        case SIGTERM:
            printf("SIGTERM: 终止\n");
            exit(0);
            break;
        default:
            printf("未知信号\n");
            break;
    }
}

int main() {
    // 注册信号处理函数
    signal(SIGINT, sigstop);   // 当接收到SIGINT（通常是通过按下Ctrl+C触发）时，调用sigstop函数
    signal(SIGQUIT, sigstop);  // 当接收到SIGQUIT（通常是通过按下Ctrl+\触发）时，调用sigstop函数
    signal(SIGTERM, sigstop);  // 当接收到SIGTERM（通常是通过kill命令触发）时，调用sigstop函数

    // 无限循环，等待信号触发
    while (1) {
        printf("等待信号...\n");
        sleep(1);
    }

    return 0;
}
#endif

#if 1


// 信号处理函数，接收一个整数型的信号编号
void sigstop(int signum) {
    printf("收到信号 %d\n", signum);

    // 根据不同信号采取相应的处理措施
    switch (signum) {
        case SIGINT:
            printf("SIGINT: 中断\n");
            exit(0);
            break;
        case SIGQUIT:
            printf("SIGQUIT: 退出\n");
            exit(0);
            break;
        case SIGTERM:
            printf("SIGTERM: 终止\n");
            exit(0);
            break;
        default:
            printf("未知信号\n");
            break;
    }
}

int main() {
    // 注册信号处理函数
    signal(SIGINT, sigstop);   // 当接收到SIGINT（通常是通过按下Ctrl+C触发）时，调用sigstop函数
    signal(SIGQUIT, sigstop);  // 当接收到SIGQUIT（通常是通过按下Ctrl+\触发）时，调用sigstop函数
    signal(SIGTERM, sigstop);  // 当接收到SIGTERM（通常是通过kill命令触发）时，调用sigstop函数

    // 无限循环，等待信号触发
    while (1) {
        printf("等待信号...\n");
        sleep(1);
    }

    return 0;
}
#endif