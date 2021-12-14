#pragma once

#include <coroutine>

#include "DebugLog.h"

// awaiter
struct ASAwaiter // Always Suspend Awaiter
{
    ASAwaiter() {
        DebugLog("ASAwaiter ctor");
    }

    ~ASAwaiter() {
        DebugLog("ASAwaiter dtor");
    }

    bool await_ready() {
        DebugLog("ASAwaiter::await_ready");
        return false;
    }

    void await_suspend(std::coroutine_handle<>) {
        DebugLog("ASAwaiter::await_suspend");
    }

    void await_resume() {
        DebugLog("ASAwaiter::await_resume");
    }
};

// class generator
template <typename U>
class GeneratorPromise;

template <typename T>
class Generator;

template <typename R, typename... Args>
struct std::coroutine_traits<Generator<R>, Args...> {
    using promise_type = GeneratorPromise<R>;
};

template <typename T>
class Generator {
    std::coroutine_handle<GeneratorPromise<T>> handle_;
public:

    class Iterator {
        Generator<T>& owner_;
        bool done_;
    public:
        Iterator(Generator<T>& g, bool done)
            : owner_(g), done_(done) {
            if (!done)
                MoveNext();
        }
        void MoveNext() {
            owner_.handle_.resume();
            done_ = owner_.handle_.done();
        }
        Iterator& operator++() {
            MoveNext();
            return *this;
        }
        bool operator!=(const Iterator& other) const {
            return done_ != other.done_;
        }
        T operator*() const {
            return owner_.handle_.promise().GetValue();
        }
    };

    Iterator begin() {
        return Iterator{ *this, false };
    }

    Iterator end() {
        return Iterator{ *this, true };
    }

    Generator(std::coroutine_handle<GeneratorPromise<T>> handle)
        : handle_(handle)
    {
    }

    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;

    Generator(Generator&& gen)
        : handle_(gen.handle_)
    {
        gen.handle_ = nullptr;
    }

    ~Generator() {
        if (handle_)
            handle_.destroy();
    }

    Generator& operator=(Generator&& gen) {
        handle_ = gen.handle_;
        gen.handle_ = nullptr;

        return *this;
    }

    bool GetNext() {
        handle_.resume();
        return !handle_.done();
    }

    T GetValue() {
        return handle_.promise().GetValue();
    }
};

// return object 
template <typename TT>
class GeneratorPromise {
    TT value_{0};
public:
    GeneratorPromise() {}
    ~GeneratorPromise() {}

    Generator<TT> get_return_object() {
        return Generator<TT>{
            std::coroutine_handle<GeneratorPromise>::from_promise(*this)};
    }

    ASAwaiter initial_suspend() {
        return ASAwaiter{};
    }

    ASAwaiter yield_value(TT value) {
        this->value_ = value;
        return ASAwaiter{};
    }

    void return_void() {
    }

    ASAwaiter final_suspend() noexcept {
        return ASAwaiter{};
    }

    void unhandled_exception() {
    }

    TT GetValue() {
        return value_;
    }
};

// test
Generator<double> SquaresGenerator(int count)
{
    for (int i = 1; i < count + 1; ++i)
    {
        co_yield std::pow(i, 2);
    }
}

void TestGenegatorCoro()
{
    DebugLog("Calling coroutine");
    auto sqGen = SquaresGenerator(3);
    while (sqGen.GetNext())
    {
        DebugLog("Get value");
        DebugLog(sqGen.GetValue());
    }
}
