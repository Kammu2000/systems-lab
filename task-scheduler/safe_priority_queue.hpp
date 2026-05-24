#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

struct Task {
  std::function<void()> fn;
  int priority;
};

class Comparator {
public:
  bool operator()(const Task &a, const Task &b) {
    return a.priority < b.priority;
  }
};

class SafePriorityQueue {
private:
  std::priority_queue<Task, std::vector<Task>, Comparator> pq;
  std::mutex queue_mutex;
  std::condition_variable cv;
  bool closed = false;

public:
  void push(Task task) {
    {
      std::lock_guard<std::mutex> lock(queue_mutex);

      if (closed)
        throw std::runtime_error("priority queue is closed");

      pq.emplace(std::move(task));
    }

    cv.notify_one();
  }

  bool pop(Task &task) {
    std::unique_lock<std::mutex> lock(queue_mutex);
    cv.wait(lock, [this] { return closed || !pq.empty(); });

    if (pq.empty() && closed)
      return false;

    task = std::move(pq.top());
    pq.pop();

    return true;
  }

  void close() {
    {
      std::lock_guard<std::mutex> lock(queue_mutex);
      closed = true;
    }

    cv.notify_all();
  }
};
