#pragma once

#include <vector>
#include <atomic>
#include <mutex>

#include "ithread_pool.h"
#include "blocking_queue.h"
#include "executor.h"

namespace concur
{

class StaticThreadPool : public IThreadPool
{
public:
    explicit StaticThreadPool(size_t workers);
    ~StaticThreadPool();

    void Execute(Task&& task);

    // no-copyable
    StaticThreadPool(const StaticThreadPool&) = delete;
    StaticThreadPool operator=(const StaticThreadPool&) = delete;
    // schedules task for execution in one of the worker threads
    void Submit(Task task);
    // gracefull shutdown. 
    // waits until outstanding work count has reaced 0
    // and joins worker threads
    void Join();
    // hard shutdown. joins worker threads asap
    void Shutdown();

    // local current thread pool from worker thread
    static StaticThreadPool* Current();
private:
    void StartWorkersThreads(size_t workers);
    void WorkerRoutine(StaticThreadPool* main_pool);
    void CloseThreads();

private:
    std::vector<std::thread> workers_;
    UnboundedBlockingQueue<Task> task_queue_;

    std::atomic<size_t> tasks_count_;
    std::atomic<bool> hasJoin_{false};
    std::mutex mutex_;
};

inline StaticThreadPool* Current() {
    return StaticThreadPool::Current();
}

IThreadPoolPtr MakeStaticPool(int threads_num);

} // concur
