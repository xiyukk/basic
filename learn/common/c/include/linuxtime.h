#include <iostream>
#include <ctime>
#include <chrono>

class Timer {
public:
    Timer() {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start_);
    }

    ~Timer() {
        clock_gettime(CLOCK_MONOTONIC_RAW, &end_);
        auto duration = timespec_diff_in_ms(end_, start_);
        std::cout << duration << "ms" << std::endl;
    }

    void start() {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start_);
    }

    void end() {
        clock_gettime(CLOCK_MONOTONIC_RAW, &end_);
        auto duration = timespec_diff_in_ms(end_, start_);
        std::cout << duration << "ms" << std::endl;
    }

private:
    timespec start_;
    timespec end_;

    double timespec_diff_in_ms(const timespec& end, const timespec& start) {
        double duration = (end.tv_sec - start.tv_sec) * 1000.0;
        duration += (end.tv_nsec - start.tv_nsec) / 1000000.0;
        return duration;
    }
};

