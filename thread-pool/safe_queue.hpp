#pragma once
#include <condition_variable>
#include <mutex>
#include <queue>
#include <stdexcept>

template <typename T> class SafeQueue {
private:
  std::queue<T> q;
  std::mutex queue_mutex;
  std::condition_variable cv;
  bool closed = false;

public:
  void push(T task) {
    {
      std::lock_guard<std::mutex> lock(queue_mutex);
      // we need to check closed after locking queue because no other thread can
      // modify any queue state at same time causing race condition
      if (closed)
        throw std::runtime_error("queue closed");
      q.emplace(std::move(task));
    }

    cv.notify_one();
  }

  bool pop(T &task) {
    std::unique_lock<std::mutex> lock(queue_mutex);

    cv.wait(lock, [this] { return closed || !q.empty(); });

    if (q.empty())
      return false;

    task = std::move(q.front());
    q.pop();

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
