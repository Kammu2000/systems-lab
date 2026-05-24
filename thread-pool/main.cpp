#include "thread_pool.hpp"
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

constexpr int TOTAL_TASKS = 10;
constexpr int POOL_SIZE = 5;

int main()
{
    ThreadPool pool(POOL_SIZE);
    std::mutex output_mutex;

    for (int i = 1; i <= TOTAL_TASKS; i++)
    {
        pool.enqueue([i, &output_mutex] {
            {
                std::lock_guard<std::mutex> lock(output_mutex);
                std::cout << "Task " << i << " running on thread : " << std::this_thread::get_id()
                          << "\n";
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
        });
    }

    std::lock_guard<std::mutex> lock(output_mutex);
    std::cout << "Main thread stopped pushing tasks" << "\n";
    return 0;
}
