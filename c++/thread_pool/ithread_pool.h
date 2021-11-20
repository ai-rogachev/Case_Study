#pragma once
#include "executor.h"

namespace concur
{

struct IThreadPool : public IExecutor {
  // Graceful shutdown
  // Wait until the pool has no more outstanding work
  // and stop the threads
  virtual void Join() = 0;

  // Hard shutdown
  // Just stop as soon as possible ignoring all scheduled tasks
  virtual void Shutdown() = 0;

  // virtual size_t ExecutedTaskCount() const = 0;

  virtual ~IThreadPool() = default;
};

using IThreadPoolPtr = std::shared_ptr<IThreadPool>;

}