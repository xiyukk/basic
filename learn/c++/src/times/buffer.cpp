#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

// 用环形队列来实现
template<typename T>
class Buffer {
public:
    explicit Buffer(size_t size) : buffer(size) {}

    void produce(const T& item) {
        std::unique_lock<std::mutex> lock(mutex);
        full_condition.wait(lock, [this]() { return !is_full(); });

        buffer[write_index] = item;
        write_index = (write_index + 1) % buffer.size();

        // std::cout << "Produced: " << item << std::endl;

        empty_condition.notify_one();
    }

    T consume() {
        std::unique_lock<std::mutex> lock(mutex);
        empty_condition.wait(lock, [this]() { return !is_empty(); });

        T item = buffer[read_index];
        read_index = (read_index + 1) % buffer.size();

        // std::cout << "Consumed: " << item << std::endl;

        full_condition.notify_one();

        return item;
    }

private:
    bool is_full() const {
        return (write_index + 1) % buffer.size() == read_index;
    }

    bool is_empty() const {
        return write_index == read_index;
    }

    std::vector<T> buffer;
    size_t read_index = 0;
    size_t write_index = 0;

    std::mutex mutex;
    std::condition_variable empty_condition;
    std::condition_variable full_condition;
};

// 用队列来实现
/* #include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class Buffer {
public:
    void produce(const T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        buffer_.push(item);
        lock.unlock();
        cond_var_.notify_one();
    }

    bool consume(T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_var_.wait(lock, [this]() { return !buffer_.empty(); });
        
        if (!buffer_.empty()) {
            item = buffer_.front();
            buffer_.pop();
            return true;
        }
        return false;
    }

private:
    std::mutex mutex_;
    std::condition_variable cond_var_;
    std::queue<T> buffer_;
}; */


#if 0
// 单个生产者消费者线程
void producer(Buffer<int>& buffer, int start, int end) {
    for (int i = start; i <= end; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        buffer.produce(i);
    }
}

void consumer(Buffer<int>& buffer, int count) {
    for (int i = 0; i < count; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        buffer.consume();
    }
}

int main() {
    const int buffer_size = 5;
    const int producer_count = 10;
    const int consumer_count = 10;

    Buffer<int> buffer(buffer_size);

    std::thread producer_thread(producer, std::ref(buffer), 1, producer_count);
    std::thread consumer_thread(consumer, std::ref(buffer), consumer_count);

    producer_thread.join();
    consumer_thread.join();

    return 0;
}

#endif

void producer(Buffer<int>& buffer, int id, int start, int end) {
    for (int i = start; i <= end; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Producer " << id << " producing: " << i << std::endl;
        buffer.produce(i);
    }
}

void consumer(Buffer<int>& buffer, int id, int count) {
    for (int i = 0; i < count; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        int item = buffer.consume();
        std::cout << "Consumer " << id << " consumed: " << item << std::endl;
    }
}

int main() {
    const int buffer_size = 5;
    const int producer_count = 10;
    const int consumer_count = 10;
    const int num_producers = 4;
    const int num_consumers = 4;

    Buffer<int> buffer(buffer_size);

    // Create multiple producer threads
    std::vector<std::thread> producer_threads;
    for (int i = 0; i < num_producers; ++i) {
        producer_threads.emplace_back(producer, std::ref(buffer), i + 1, i * producer_count + 1, (i + 1) * producer_count);
    }

    // Create multiple consumer threads
    std::vector<std::thread> consumer_threads;
    for (int i = 0; i < num_consumers; ++i) {
        consumer_threads.emplace_back(consumer, std::ref(buffer), i + 1, consumer_count);
    }

    // Join producer threads
    for (auto& t : producer_threads) {
        t.join();
    }

    // Join consumer threads
    for (auto& t : consumer_threads) {
        t.join();
    }

    return 0;
}