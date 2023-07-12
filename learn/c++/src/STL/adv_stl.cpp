#if 1
// 使用 std::find 查找元素
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {4, 2, 9, 5, 1, 8};

    int target = 5;
    auto it = std::find(numbers.begin(), numbers.end(), target);

    if (it != numbers.end()) {
        std::cout << "Found " << target << " at position " << std::distance(numbers.begin(), it) << std::endl;
    } else {
        std::cout << target << " not found in the vector" << std::endl;
    }

    return 0;
}

#endif

#if 0
// 使用 std::count 统计元素出现次数
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 2, 4, 2, 5, 2};

    int target = 2;
    int count = std::count(numbers.begin(), numbers.end(), target);

    std::cout << target << " appears " << count << " times in the vector" << std::endl;

    return 0;
}
#endif

#if 0
// 使用 std::replace 替换元素
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 2, 4, 2, 5, 2};

    int old_value = 2;
    int new_value = 99;
    std::replace(numbers.begin(), numbers.end(), old_value, new_value);

    std::cout << "Vector after replacing " << old_value << " with " << new_value << ":";
    for (int num : numbers) {
        std::cout << " " << num;
    }
    std::cout << std::endl;

    return 0;
}
#endif

#if 0
// 使用 std::transform 对元素执行操作
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> squared_numbers(numbers.size());

    std::transform(numbers.begin(), numbers.end(), squared_numbers.begin(), [](int x) { return x * x; });

    std::cout << "Squared numbers:";
    for (int num : squared_numbers) {
        std::cout << " " << num;
    }
    std::cout << std::endl;

    return 0;
}
#endif

#if 0
使用 std::sort 和 std::unique 删除重复元素

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 2, 4, 2, 5, 2};

    // 需要先对容器进行排序
    std::sort(numbers.begin(), numbers.end());

    // 使用 std::unique 移除重复元素
    auto last = std::unique(numbers.begin(), numbers.end());

    // 删除重复元素后的容器末尾
    numbers.erase(last, numbers.end());

    std::cout << "Vector after removing duplicates:";
    for (int num : numbers) {
        std::cout << " " << num;
    }
    std::cout << std::endl;

    return 0;
}
#endif

#if 0

#endif
