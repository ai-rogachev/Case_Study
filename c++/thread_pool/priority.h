#pragma once

#include "executor.h"

namespace concur {

struct IPriorityExecutor {
  virtual ~IPriorityExecutor() = default;

  // Higher-priority tasks first!
  virtual void Execute(int priority, Task&& task) = 0;

  virtual IExecutorPtr FixPriority(int priority) = 0;
};

using IPriorityExecutorPtr = std::shared_ptr<IPriorityExecutor>;

IPriorityExecutorPtr MakePriorityExecutor(IExecutorPtr executor);

}  // namespace await::executors