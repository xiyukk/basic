#include <iostream>
#include <chrono>
#include "threadpool.h"

void print_hello(int id) {
    std::cout << "Hello from task " << id << std::endl;
}

int main() {
    ThreadPool pool(4);

    for (int i = 0; i < 10; ++i) {
        pool.enqueue([i] { print_hello(i); });
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}