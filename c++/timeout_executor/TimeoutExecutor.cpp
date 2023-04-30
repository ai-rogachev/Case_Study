#include "TimeoutExecutor.h"

namespace concur
{
    TimeoutExecutor::TimeoutExecutor()
        : m_threadPool(8)
    {
    }
    TimeoutExecutor::~TimeoutExecutor()
    {
        Join();
    }
    void TimeoutExecutor::Execute(task_t&& task)
    {
        ++m_count;
        m_threadPool.Submit([&, tsk = std::move(task)]() {
            // execute user function
            tsk();
            --m_count;
        });
    }

    bool TimeoutExecutor::WaitFor(std::chrono::milliseconds timeOutInMillisec)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_readyOrTimeout.wait_for(lock, timeOutInMillisec, 
            [&]() { return m_count == 0; }
        );
    }
    void TimeoutExecutor::Join()
    {
        m_threadPool.Join();
    }
}