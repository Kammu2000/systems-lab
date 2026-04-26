#include "thread_pool.hpp"
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

int main() {
  ThreadPool pool(4);
  std::mutex output_mutex;

  for (int i = 1; i <= 10; i++) {
    pool.enqueue([i, &output_mutex] {
      {
        std::lock_guard<std::mutex> lock(output_mutex);
        std::cout << "Task " << i
                  << " running on thread : " << std::this_thread::get_id()
                  << std::endl;
      }

      std::this_thread::sleep_for(std::chrono::seconds(2));
    });
  }

  std::lock_guard<std::mutex> lock(output_mutex);
  std::cout << "Main thread stopped pushing tasks" << std::endl;
  return 0;
}
