#include <cstddef>
#include <functional>

#include "thread_pool.hpp"

ThreadPool::ThreadPool(size_t count)
{
    for (int i = 0; i < count; i++)
    {
        workers.emplace_back([this]() {
            std::function<void()> task;

            while (tasks.pop(task))
            {
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool()
{
    wait();
}

void ThreadPool::enqueue(std::function<void()> task)
{
    tasks.push(std::move(task));
}

void ThreadPool::wait()
{
    tasks.close();
    for (auto& worker : workers)
    {
        if (worker.joinable())
        {
            worker.join();
        }
    }
}
