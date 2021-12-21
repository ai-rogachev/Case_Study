#ifndef FUTURE_IMPL
#error Do not include this file directly
#endif

namespace future_impl
{
	//////////////////////////////////////////////////////////////////////
	// Static constructors

	template <typename T>
	Future<T> Future<T>::Completed(T value) {
		auto state = MakeSharedState<T>();
		state->SetResult(std::move(value));
		return Future<T>(std::move(state));
	}

	template <typename T>
	Future<T> Future<T>::Invalid() {
		return Future<T>(nullptr);
	}

	//////////////////////////////////////////////////////////////////////

	// GetValue

	template <typename T>
	T Future<T>::GetValue()&& {
		return ReleaseState()->GetResult();
	}
}