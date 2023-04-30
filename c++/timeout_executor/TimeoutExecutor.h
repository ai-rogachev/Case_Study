#pragma once

#include <chrono>
#include <functional>
#include <atomic>

#include "../thread_pool/thread_pool.h"

namespace concur
{
    // Execute tasks in thread pool. 
    // Return result if it will complited befor timeout.
    // If task not comploted befor tiime out,
    // it will continue to work.
    class TimeoutExecutor
    {
    public:
        using task_t = std::function<void()>;

        TimeoutExecutor();
        ~TimeoutExecutor();

        // put in queue
        void Execute(task_t&& task);
                
        // is ready
        bool WaitFor(std::chrono::milliseconds timeOutInMillisec);

        void Join();
    private:
        concur::StaticThreadPool m_threadPool;
        std::condition_variable m_readyOrTimeout;
        std::mutex m_mutex;

        std::atomic<int> m_count;
    };
}
