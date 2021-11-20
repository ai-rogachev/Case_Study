#pragma once 

#include <mutex>
#include <queue>
#include <condition_variable>
#include <optional>

namespace concur 
{

// Unbounded blocking multi-producers/multi-consumers queue
template <typename T>
class UnboundedBlockingPriorQueue
{
public:
    bool Put(T value)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        if (closed_)
            return false;

        buffer_.push(std::move(value));
        hasValue_.notify_all();

        return true;
    }

    std::optional<T> Take()
    {
        std::unique_lock<std::mutex> lock(mutex_);

        hasValue_.wait(lock,
            [&]() { return !buffer_.empty() || closed_; }
        );

        if (closed_ && buffer_.empty())
            return std::nullopt;

        auto value = std::move(const_cast<T&>(buffer_.top()));
        buffer_.pop();

        return value;
    }

    void Close()
    {
        CloseImpl(false);
    }

    void Cancel()
    {
        CloseImpl(true);
    }

private:
    void CloseImpl(bool clear)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        closed_ = true;

        if (clear)
            buffer_.clear();

        hasValue_.notify_all();
    }

private:
    std::priority_queue<T> buffer_;
    std::mutex mutex_;
    std::condition_variable hasValue_;
    bool closed_{ false };
};

} // concur