#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t numThreads) : stop(false)
{
    for (size_t i = 0; i < numThreads; i++)
    {
        workers.emplace_back([this] {
            while (!this->stop)
            {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->queueMutex);
                    this->cv.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
                    if (this->stop && this->tasks.empty())
                    {
                        return;
                    }
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool()
{
    stop = true;
    cv.notify_all();
    for (auto &t : workers)
    {
        if (t.joinable())
        {
            t.join();
        }
    }
}
