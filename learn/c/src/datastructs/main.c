#include <stdio.h>

// array.
/* int main() {
    // 定义一个整型数组，包含5个元素
    int numbers[5] = {1, 2, 3, 4, 5};

    // 遍历数组并打印每个元素的值
    for (int i = 0; i < 5; i++) {
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }

    return 0;
} */


//struct
/* // 定义一个名为Student的结构体
struct Student {
    int id;          // 学生ID
    char name[20];   // 学生姓名
    float score;     // 学生分数
};

int main() {
    // 创建一个Student结构体实例
    struct Student student1 = {1, "John Doe", 85.0};

    // 打印结构体的成员
    printf("ID: %d\n", student1.id);
    printf("Name: %s\n", student1.name);
    printf("Score: %.2f\n", student1.score);

    return 0;
} */


//enum
// 定义一个名为Weekday的枚举类型
/* enum Weekday {
    Sunday,    // 0
    Monday,    // 1
    Tuesday,   // 2
    Wednesday, // 3
    Thursday,  // 4
    Friday,    // 5
    Saturday   // 6
};

int main() {
    // 创建一个Weekday枚举变量
    enum Weekday today = Wednesday;

    // 打印枚举值
    printf("Today is: %d\n", today);

    return 0;
} */


// union

// 定义一个名为Data的联合类型
/* union Data {
    int integer;      // 整型
    float floating;   // 浮点型
    char character;   // 字符型
};

int main() {
    // 创建一个Data联合变量
    union Data data;

    // 存储整型值
    data.integer = 42;
    printf("Integer: %d\n", data.integer);

    // 存储浮点型值
    data.floating = 3.14;
    printf("Float: %.2f\n", data.floating);

    // 存储字符型值
    data.character = 'A';
    printf("Character: %c\n", data.character);

    return 0;
} */


// List
#include <stdlib.h>

// 定义链表节点结构体
struct Node {
    int data;               // 节点数据
    struct Node* next;      // 指向下一个节点的指针
};

// 创建新节点函数
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 打印链表函数
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    // 创建链表头节点
    struct Node* head = createNode(1);

    // 为链表添加节点
    head->next = createNode(2);
    head->next->next = createNode(3);

    // 打印链表
    printList(head);

    return 0;
}