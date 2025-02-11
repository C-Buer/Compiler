#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t numThreads) : stop(false), activeTasks(0)
{
    for (size_t i = 0; i < numThreads; i++)
    {
        workers.emplace_back([this] {
            while (true)
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
                activeTasks--;
                if (activeTasks.load() == 0)
                {
                    std::unique_lock<std::mutex> lk(this->queueMutex);
                    cvDone.notify_all();
                }
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

void ThreadPool::postTask(const std::function<void()> &task)
{
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        tasks.push(task);
        activeTasks++;
    }
    cv.notify_one();
}

void ThreadPool::waitAll()
{
    std::unique_lock<std::mutex> lock(queueMutex);
    cvDone.wait(lock, [this] { return this->activeTasks.load() == 0; });
}
