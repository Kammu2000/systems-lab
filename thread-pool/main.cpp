#include "thread_pool.hpp"
#include <chrono>
#include <cstddef>
#include <iostream>
#include <thread>

constexpr size_t TOTAL_TASKS = 10;
constexpr size_t POOL_SIZE = 2;

int main()
{
    ThreadPool pool(POOL_SIZE);

    auto create_task = [](size_t idx) {
        return [idx]() {
            std::cout << "Task " << idx << " running on thread : " << std::this_thread::get_id()
                      << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        };
    };

    for (int i = 1; i <= TOTAL_TASKS; i++)
    {
        pool.enqueue(create_task(i));
    }

    std::cout << "Main thread stopped pushing tasks" << "\n";
    pool.wait();
    return 0;
}
