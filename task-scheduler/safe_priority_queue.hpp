#pragma once

#include <condition_variable>
#include <cstddef>
#include <functional>
#include <mutex>
#include <queue>
#include <vector>

struct Task
{
    std::function<void()> fn;
    size_t priority;
};

class Comparator
{
  public:
    bool operator()(const Task& first, const Task& second)
    {
        return first.priority < second.priority;
    }
};

class SafePriorityQueue
{
  private:
    std::priority_queue<Task, std::vector<Task>, Comparator> pq;
    std::mutex queue_mutex;
    std::condition_variable cv;
    bool closed = false;

  public:
    void push(Task&& task);
    bool pop(Task& task);
    void close();
};
