#include <cstddef>
#include <iostream>

#include "task_scheduler.hpp"

constexpr size_t TOTAL_TASKS = 10;
constexpr size_t POOL_SIZE = 5;

int main()
{
    TaskScheduler scheduler(POOL_SIZE);

    auto create_task = [&](size_t idx) {
        return [idx] {
            {
                std::cout << "Task " << idx << " running on thread: " << std::this_thread::get_id()
                          << "\n";

                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        };
    };

    for (size_t i = 1; i <= TOTAL_TASKS; i++)
    {
        scheduler.schedule({create_task(i), i});
    }

    std::cout << "Main thread stopped pushing tasks" << "\n";

    scheduler.wait();
    return 0;
}
