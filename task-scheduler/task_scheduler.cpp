#include "safe_priority_queue.hpp"
#include <cstddef>
#include <utility>
#include "task_scheduler.hpp"

TaskScheduler::TaskScheduler(const size_t& workers_cnt)
{
    for (size_t i = 0; i < workers_cnt; i++)
    {
        workers.emplace_back([this]() {
            Task task;

            while (task_queue.pop(task))
            {
                task.fn();
            }
        });
    }
}

TaskScheduler::~TaskScheduler()
{
    wait();
}

void TaskScheduler::schedule(Task&& task)
{
    task_queue.push(std::move(task));
}

void TaskScheduler::wait()
{
    task_queue.close();

    for (auto& worker : workers)
    {
        if (worker.joinable())
        {
            worker.join();
        }
    }
}
