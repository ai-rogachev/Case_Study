#pragma once

#include <assert.h>

#include "shared_state.h"
#include "future.h"

namespace future_impl
{

template <typename T>
class Promise : public HoldState<T> 
{
  using HoldState<T>::state_;
  using HoldState<T>::CheckState;
  using HoldState<T>::ReleaseState;

public:
  Promise() : HoldState<T>(MakeSharedState<T>()) {
  }

  // One-shot
  Future<T> MakeFuture() {
    assert(!future_extracted_, "Future already extracted");
    future_extracted_ = true;
    return Future{state_};
  }

  void SetValue(T value) && {
    ReleaseState()->SetResult(std::move(value));
  }

 private:
  bool future_extracted_{false};
};

//////////////////////////////////////////////////////////////////////

// Usage:
// auto [f, p] = futures::MakeContract<T>();
// https://en.cppreference.com/w/cpp/language/structured_binding

template <typename T>
using Contract = std::pair<Future<T>, Promise<T>>;

template <typename T>
Contract<T> MakeContract()
{
    Promise<T> p;
    auto f = p.MakeFuture();
    return { std::move(f), std::move(p) };
};

} // namespace future_impl