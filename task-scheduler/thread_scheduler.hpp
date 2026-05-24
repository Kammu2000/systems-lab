#include "safe_priority_queue.hpp"
#include <thread>
#include <vector>

class TaskScheduler {
private:
  std::vector<std::thread> workers;
  SafePriorityQueue pq;

public:
};
