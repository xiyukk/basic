#include <stdio.h>
/* 
 * 在C语言中，钩子通常是一个指向函数的指针，可以在运行时动态更改。钩子函数允许用户在不修改现有代码的情况下，
 * 扩展或定制功能。下面是一个使用钩子的示例，该示例实现了一个简单的事件系统。
 */

 /* 
  * 在这个示例中，我们定义了一个名为event_handler的函数指针类型，用于处理事件。我们还定义了一个
  * 名为on_event_hook的全局钩子变量，该变量初始值为NULL。
  * 
  * 我们提供了两个函数：register_hook用于注册事件处理函数，trigger_event用于触发事件。
  * 在trigger_event函数中，我们检查on_event_hook钩子是否为NULL。如果钩子已设置（即不为NULL），
  * 我们调用它以处理事件；否则，我们打印一条消息，表明没有注册事件处理函数。
  * 
  * 在main函数中，我们首先尝试触发一个事件，但没有注册事件处理函数。然后，
  * 我们使用my_event_handler函数注册一个自定义事件处理函数，并再次触发事件。这次，注册的事件处理函数将被调用。
  */

#if 1
// 事件处理函数类型
typedef void (*event_handler)(const char *);

// 钩子函数
event_handler on_event_hook = NULL;

// 注册钩子函数
void register_hook(event_handler handler) {
    on_event_hook = handler;
}

// 触发事件
void trigger_event(const char *event_name) {
    if (on_event_hook != NULL) {
        on_event_hook(event_name);
    } else {
        printf("No event handler registered for event: %s\n", event_name);
    }
}

// 自定义事件处理函数
void my_event_handler(const char *event_name) {
    printf("Handling event: %s\n", event_name);
}

int main() {
    // 触发事件，没有注册处理函数
    trigger_event("Event1");

    // 注册自定义事件处理函数
    register_hook(my_event_handler);

    // 触发事件，已注册处理函数
    trigger_event("Event2");

    return 0;
}

#endif