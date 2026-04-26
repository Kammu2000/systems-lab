#pragma once
#include "safe_queue.hpp"
#include <cstddef>
#include <functional>
#include <thread>
#include <vector>

class ThreadPool {
public:
  ThreadPool(size_t count);
  ThreadPool(ThreadPool &&) = delete;
  ThreadPool(const ThreadPool &) = delete;
  ThreadPool &operator=(ThreadPool &&) = delete;
  ThreadPool &operator=(const ThreadPool &) = delete;
  ~ThreadPool();

  void enqueue(std::function<void()> task);

private:
  std::vector<std::thread> workers;
  SafeQueue<std::function<void()>> tasks;
};
