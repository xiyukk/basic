#include <stdio.h>

// 1、嵌套结构体
#if 0
// 定义一个名为Address的结构体
struct Address {
    char street[50];
    int houseNumber;
    char city[50];
    char country[50];
};

// 定义一个名为Person的结构体
struct Person {
    char name[50];
    int age;
    struct Address address; // 嵌套Address结构体
};

int main() {
    // 创建一个Person结构体实例
    struct Person person1 = {
        "John Doe",
        30,
        {
            "Main Street",
            123,
            "New York",
            "USA"
        }
    };

    // 打印结构体的成员
    printf("Name: %s\n", person1.name);
    printf("Age: %d\n", person1.age);
    printf("Address: %d %s, %s, %s\n",
        person1.address.houseNumber,
        person1.address.street,
        person1.address.city,
        person1.address.country
    );

    return 0;
}
#endif


// 结构体指针
#if 0
#include <stdlib.h>

struct Point {
    int x;
    int y;
};

void setPoint(struct Point* point, int x, int y) {
    point->x = x;
    point->y = y;
}

int main() {
    struct Point* point1 = (struct Point*)malloc(sizeof(struct Point));

    setPoint(point1, 10, 20);

    printf("Point coordinates: (%d, %d)\n", point1->x, point1->y);

    free(point1);
    return 0;
}
#endif


// 结构体数组
#if 0
struct Employee {
    int id;
    char name[50];
    float salary;
};

void printEmployee(struct Employee employee) {
    printf("ID: %d\n", employee.id);
    printf("Name: %s\n", employee.name);
    printf("Salary: %.2f\n", employee.salary);
}

int main() {
    struct Employee employees[3] = {
        {1, "John Doe", 50000},
        {2, "Jane Smith", 60000},
        {3, "Jim Brown", 55000}
    };

    for (int i = 0; i < 3; i++) {
        printEmployee(employees[i]);
        printf("\n");
    }

    return 0;
}
#endif


// 结构体函数参数和返回值
#if 1

struct Rectangle {
    int width;
    int height;
};

int getArea(struct Rectangle rect) {
    return rect.width * rect.height;
}

struct Rectangle doubleSize(struct Rectangle rect) {
    rect.width *= 2;
    rect.height *= 2;
    return rect;
}

int main() {
    struct Rectangle rect1 = {10, 20};

    printf("Area: %d\n", getArea(rect1));

    struct Rectangle rect2 = doubleSize(rect1);
    printf("Doubled size: %d x %d\n", rect2.width, rect2.height);

    return 0;
}
#endif