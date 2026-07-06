#pragma once

#include <cstddef>
#include <functional>
#include <thread>
#include <vector>

#include "safe_queue.hpp"

class ThreadPool
{
  public:
    ThreadPool(size_t count);
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ~ThreadPool();

    void enqueue(std::function<void()> task);
    void wait();

  private:
    std::vector<std::thread> workers;
    SafeQueue<std::function<void()>> tasks;
};
