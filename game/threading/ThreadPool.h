#pragma once

#include <condition_variable>
#include <cstddef>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

// Fixed-size worker pool. Destruction drains accepted work and joins all workers.
// The owning thread must destroy the pool; tasks must not destroy their pool.
class ThreadPool
{
public:
    explicit ThreadPool(std::size_t worker_count)
    {
        if (worker_count == 0)
            throw std::invalid_argument("ThreadPool needs at least one worker");
        try
        {
            m_workers.reserve(worker_count);
            for (std::size_t i = 0; i < worker_count; ++i)
                m_workers.emplace_back([this] { run(); });
        }
        catch (...)
        {
            stop();
            throw;
        }
    }

    ~ThreadPool() { stop(); }
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    template<class Function>
    auto submit(Function&& function) -> std::future<std::invoke_result_t<std::decay_t<Function>&>>
    {
        using Result = std::invoke_result_t<std::decay_t<Function>&>;
        auto task = std::make_shared<std::packaged_task<Result()>>(std::forward<Function>(function));
        auto result = task->get_future();
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_stopping)
                throw std::runtime_error("ThreadPool is stopping");
            m_tasks.emplace([task] { (*task)(); });
        }
        m_ready.notify_one();
        return result;
    }

private:
    void run()
    {
        for (;;)
        {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                m_ready.wait(lock, [this] { return m_stopping || !m_tasks.empty(); });
                if (m_stopping && m_tasks.empty())
                    return;
                task = std::move(m_tasks.front());
                m_tasks.pop();
            }
            // Do not hold the queue mutex while executing user work.
            task();
        }
    }

    void stop()
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_stopping = true;
        }
        m_ready.notify_all();
        for (auto& worker : m_workers)
            if (worker.joinable())
                worker.join();
    }

    std::mutex m_mutex;
    std::condition_variable m_ready;
    std::queue<std::function<void()>> m_tasks;
    std::vector<std::thread> m_workers;
    bool m_stopping = false;
};
