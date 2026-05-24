#include "safe_priority_queue.hpp"

void SafePriorityQueue::push(Task&& task)
{
    {
        std::lock_guard<std::mutex> lock(queue_mutex);

        if (closed)
        {
            throw std::runtime_error("priority queue is closed");
        }

        pq.emplace(std::move(task));
    }

    cv.notify_one();
}

bool SafePriorityQueue::pop(Task& task)
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    cv.wait(lock, [this] { return closed || !pq.empty(); });

    if (pq.empty() && closed)
    {
        return false;
    }

    task = pq.top();
    pq.pop();

    return true;
}

void SafePriorityQueue::close()
{
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        closed = true;
    }

    cv.notify_all();
}
