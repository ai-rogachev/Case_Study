#include "priority.h"
#include "blocking_priority_queue.h"

#include <iostream>

namespace concur {

class PriorityExecutor : public IPriorityExecutor, public IExecutor {
  struct PriorTask
  {
    int priority;
    Task task;

    PriorTask(int prior, Task&& task) :
      priority(prior),
      task(std::move(task))
    {
    }

    PriorTask(PriorTask&& prTask) :
      priority(prTask.priority),
      task(std::move(prTask.task))
    {
    }

    PriorTask& operator=(PriorTask&& prTask)
    {
      this->priority = prTask.priority;
      this->task = std::move(prTask.task);
      return *this;
    }
    friend bool operator< (const PriorTask& a, const PriorTask& b)
    {
      return a.priority < b.priority;
    }
  };
  using PriorityQueueType =
      std::shared_ptr<UnboundedBlockingPriorQueue<PriorTask>>;

public:
  PriorityExecutor(IExecutorPtr executor, int priority = 0) :
       executor_(executor),
       queue_ptr_(nullptr),
       priority_(priority)
  {
    if (!queue_ptr_)
      queue_ptr_ = std::make_shared<UnboundedBlockingPriorQueue<PriorTask>>();
  }

  PriorityExecutor(const PriorityExecutor& executor, int priority) :
      executor_(executor.executor_),
      queue_ptr_(executor.queue_ptr_),
      priority_(priority)
  {
  }

  void Execute(Task&& task)
  {
    queue_ptr_->Put(PriorTask{priority_, std::move(task)});
    executor_->Execute(
        [queue_ptr = queue_ptr_]() {
          auto task = queue_ptr->Take();
          task->task();
        }
    );
  }

  void Execute(int priority, Task&& task)
  {
    queue_ptr_->Put(PriorTask{priority, std::move(task)});
    executor_->Execute(
        [queue_ptr = queue_ptr_]() {
          auto task = queue_ptr->Take();
          task->task();
        }
    );
  }

  IExecutorPtr FixPriority(int priority)
  {
    return std::make_shared<PriorityExecutor>(*this, priority);
  }
 private:
  IExecutorPtr executor_;
  PriorityQueueType queue_ptr_;
  int priority_;
  std::mutex mutex;
};

IPriorityExecutorPtr MakePriorityExecutor(IExecutorPtr executor) {
  return std::make_shared<PriorityExecutor>(executor);
}

}  // namespace await::executors