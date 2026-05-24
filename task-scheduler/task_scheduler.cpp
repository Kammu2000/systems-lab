#include "safe_priority_queue.hpp"
#include <utility>
#include "task_scheduler.hpp"

TaskScheduler::TaskScheduler()
{
    workers.emplace_back([this]() {
        Task task;

        while (task_queue.pop(task))
        {
            task.fn();
        }
    });
}

TaskScheduler::~TaskScheduler()
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

void TaskScheduler::schedule(Task&& task)
{
    task_queue.push(std::move(task));
}
