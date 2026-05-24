#include "safe_priority_queue.hpp"
#include <cstddef>
#include <thread>
#include <vector>

class TaskScheduler
{
  public:
    TaskScheduler(const size_t& workers_cnt);
    TaskScheduler(TaskScheduler&&) = delete;
    TaskScheduler(const TaskScheduler&) = delete;
    TaskScheduler& operator=(TaskScheduler&&) = delete;
    TaskScheduler& operator=(const TaskScheduler&) = delete;
    ~TaskScheduler();

    void schedule(Task&& task);
    void wait();

  private:
    std::vector<std::thread> workers;
    SafePriorityQueue task_queue;
};
