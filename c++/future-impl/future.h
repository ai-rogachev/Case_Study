#pragma once

namespace future_impl
{

//////////////////////////////////////////////////////////////////////

template <typename T>
class Promise;

//////////////////////////////////////////////////////////////////////

template <typename T>
class Future : public HoldState<T> 
{
  friend class Promise<T>;
  template<typename U> friend class Future;

  using HoldState<T>::state_;
  using HoldState<T>::HasState;
  using HoldState<T>::CheckState;
  using HoldState<T>::ReleaseState;

 public:
  // Static constructors

  static Future<T> Completed(T value);
  static Future<T> Invalid();

  // State

  // True if this future has a shared state
  // False if result has already been consumed
  // 1) synchronously via GetReadyResult/GetResult or
  // 2) asynchronously via Subscribe
  bool IsValid() const {
    return HasState();
  }

  // Non-blocking
  // True if this future has result in its shared state
  bool IsReady() const {
    CheckState();
    return state_->HasResult();
  }

  // Non-blocking, one-shot
  // Pre-condition: IsReady() == true
  T GetReadyResult() && {
    return ReleaseState()->GetReadyResult();
  }

  // Blocking, one-shot
  // Returns value or throws an exception
  T GetValue() &&;

 private:
  explicit Future(StateRef<T> state)
      : HoldState<T>(std::move(state)) {
  }
};

}

/* 
 With templates, this is no longer possible
 almost all template methods need to be defined 
 in the header. To separated them at least on 
 a logical level, some people put the declarations 
 in the header but move all implementations of template 
 methods to .ipp files (i for "inline") and include the
 .ipp file at the end of the header.
*/

#define FUTURE_IMPL
#include "future.ipp"
#undef FUTURE_IMPL