#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>
#include <vector>


class ThreadPool
{
  private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable cv;
    std::atomic<bool> stop;

  public:
    explicit ThreadPool(size_t numThreads);
    ~ThreadPool();

    template <class F> auto postTask(F &&f) -> std::future<std::invoke_result_t<F>>
    {
        using RetType = std::invoke_result_t<F>;
        auto taskPtr = std::make_shared<std::packaged_task<RetType()>>(std::forward<F>(f));
        std::future<RetType> res = taskPtr->get_future();
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            tasks.push([taskPtr]() { (*taskPtr)(); });
        }
        cv.notify_one();
        return res;
    }
};

#endif
