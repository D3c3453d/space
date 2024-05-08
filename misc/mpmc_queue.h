#pragma once
#include <deque>
#include <mutex>

template <class T>
class MutexMPMCQueue {
public:
    MutexMPMCQueue() = default;

public:
    void push(T elem) {
        std::lock_guard guard(_mtx);
        _queue.push_back(std::move(elem));
    }

    void pop(T& elem) {
        std::lock_guard guard(_mtx);
        elem = std::move(_queue.front());
        _queue.pop_front();
    }

    size_t size() {
        std::lock_guard guard(_mtx);
        return _queue.size();
    }

private:
    std::deque<T> _queue;
    std::mutex _mtx;
};