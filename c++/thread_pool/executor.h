#pragma once

#include <functional>
#include <memory>

using Task = std::function<void()>;

namespace concur {

struct IExecutor {
  virtual ~IExecutor() = default;

  // Schedules task for execution
  virtual void Execute(Task&& task) = 0;
};

using IExecutorPtr = std::shared_ptr<IExecutor>;

}  // namespace await::executors