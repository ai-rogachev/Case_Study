#include "thread_pool.h"

#include <cassert>
#include <optional>

namespace concur
{
////////////////////////////////////////////////////////////////////////////////

static thread_local StaticThreadPool* pool{nullptr};

////////////////////////////////////////////////////////////////////////////////

StaticThreadPool::StaticThreadPool(size_t workers) 
{
    StartWorkersThreads(workers);
}

StaticThreadPool::~StaticThreadPool()
{
    if (!workers_.empty())
        Shutdown();
    assert(workers_.empty());
}

void StaticThreadPool::Execute(Task&& task)
{
    Submit(task);
}

void StaticThreadPool::Submit(Task task)
{
    task_queue_.Put(std::move(task));
    tasks_count_.fetch_add(1);
}

void StaticThreadPool::Join()
{
    hasJoin_.store(true);
    if (tasks_count_ == 0)
    {
        task_queue_.Close();
    }
    CloseThreads();
}

void StaticThreadPool::CloseThreads()
{
    for (auto& worker : workers_)
    {
        worker.join();
    }
    workers_.clear();
}

void StaticThreadPool::Shutdown()
{
    hasJoin_.store(true);
    task_queue_.Cancel();
    CloseThreads();
}

void StaticThreadPool::StartWorkersThreads(size_t workers)
{
    for (size_t i = 0; i < workers; ++i) 
    {
        workers_.emplace_back(
            [this](){ WorkerRoutine(this); }
        );
    }
}

void StaticThreadPool::WorkerRoutine(StaticThreadPool* main_pool)
{
    while (true)
    {
        std::optional<Task> task = task_queue_.Take();
        if (!task)
        {
            break;
        }

        try 
        {
            Task& tsk = task.value();
            tsk();
        }
        catch (...) {
        }

        tasks_count_.fetch_sub(1);
        if (tasks_count_ == 0 && hasJoin_) {
            task_queue_.Close();
            break;
        }
    }
}

StaticThreadPool* StaticThreadPool::Current() {
    return pool;
}

IThreadPoolPtr MakeStaticPool(int threads_num)
{
    return std::make_shared<StaticThreadPool>(threads_num);
}

} // concur