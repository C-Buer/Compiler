#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>


class ThreadPool
{
  private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable cv;
    std::condition_variable cvDone;
    std::atomic<bool> stop;
    std::atomic<int> activeTasks;

  public:
    explicit ThreadPool(size_t numThreads);
    ~ThreadPool();
    void postTask(const std::function<void()> &task);
    void waitAll();
};

#endif
