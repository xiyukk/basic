#include <iostream>
#include <thread>
#include <future>

/* 
 使用std::promise和std::future实现了异步操作。add函数在一个单独的线程中执行，
 并将结果存储在std::promise对象中。主线程通过与std::promise关联的std::future对象等待结果并获取结果。
 */


void add(int a, int b, std::promise<int> result_promise) {
  int sum = a + b;
  result_promise.set_value(sum); // 设置结果
}

int main() {
  std::promise<int> result_promise;
  std::future<int> result_future = result_promise.get_future();

  std::thread t(add, 2, 3, std::move(result_promise));

  int sum = result_future.get();
  std::cout << "Sum: " << sum << std::endl;

  t.join();
  return 0;
}