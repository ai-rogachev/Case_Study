#pragma once
#include <chrono>

template <typename Time = std::chrono::nanoseconds,
          typename Clock = std::chrono::high_resolution_clock>
class perf_timer
{
public:

  template <typename F, typename... Args>
  static Time duration(F&& f, Args... args)
  {
    auto start = Clock::now();
    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    auto end = Clock::now();
    return std::chrono::duration_cast<Time>(end - start);
  }

  void start()
  {
    start_ = Clock::now();
  }

  Time end()
  {
      Clock::time_point end = Clock::now();
      return std::chrono::duration_cast<Time>(end - start_);
  }

private:
    typename Clock::time_point start_;
};