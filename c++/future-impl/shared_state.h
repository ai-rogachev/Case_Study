#pragma once 

#include <mutex>
#include <functional>
#include <condition_variable>

// dif method to impl. future
// lockfree state machine for future from Folly
// https://github.com/facebook/folly/blob/e9a24429e17e85539143fb4192d22ac89f012906/folly/futures/detail/Core.h#L247

namespace future_impl
{

//////////////////////////////////////////////////////////////////////

// State shared between Promise and Future

template <typename T>
class SharedState 
{
public:
  SharedState() {
  }
  ~SharedState() {
  }

  void SetResult(T&& result) {
      std::lock_guard<std::mutex> lock(mutex_);
      result_.emplace(std::move(result));
      has_value_.notify_all();
  }

  bool HasResult() const {
      return result_ != std::nullopt;
  }

  T GetResult() {
      std::unique_lock<std::mutex> lock(mutex_);
      has_value_.wait(lock, [&]() {
          return result_ != std::nullopt;
          });
      return GetReadyResult();
  }

  // Precondition: f.IsReady() == true
  T GetReadyResult() {
      return std::move(*result_);
  }

private:
    std::optional<T> result_;
    std::mutex mutex_;
    std::condition_variable has_value_;
};
    
//////////////////////////////////////////////////////////////////////

template <typename T>
using StateRef = std::shared_ptr<SharedState<T>>;

template <typename T>
inline StateRef<T> MakeSharedState() {
  return std::make_shared<SharedState<T>>();
}

//////////////////////////////////////////////////////////////////////

// Common base for Future and Promise
template <typename T>
class HoldState 
{
protected:
    HoldState(StateRef<T> state) : state_(std::move(state)) {
    }
    // Only Movable
    HoldState(HoldState&& other) = default;
    HoldState& operator=(HoldState&& other) = default;

    // Non-copable
    HoldState(const HoldState& other) = delete;
    HoldState& operator=(const HoldState& other) = delete;

    StateRef<T> ReleaseState() {
        CheckState();
        return std::move(state_);
    }

    bool HasState() const {
        return (bool)state_;
    }

    void CheckState() const {
        assert(HasState(), "No shared state or shared state released");
    }

protected:
    StateRef<T> state_;
};

} // namespace future_impl
