#include "safe_priority_queue.hpp"
#include <thread>
#include <vector>

class TaskScheduler
{
  public:
    TaskScheduler();
    TaskScheduler(TaskScheduler&&) = delete;
    TaskScheduler(const TaskScheduler&) = delete;
    TaskScheduler& operator=(TaskScheduler&&) = delete;
    TaskScheduler& operator=(const TaskScheduler&) = delete;
    ~TaskScheduler();

    void schedule(Task&& task);

  private:
    std::vector<std::thread> workers;
    SafePriorityQueue task_queue;
};
