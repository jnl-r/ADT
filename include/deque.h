#pragma once
#include <cstddef>

template<typename T>
class Deque {
public:
    virtual ~Deque() {}

    virtual void pushFront(const T& value) = 0;
    virtual void pushBack(const T& value) = 0;

    virtual T popFront() = 0;
    virtual T popBack() = 0;

    virtual const T& front() const = 0;
    virtual const T& back() const = 0;

    virtual bool empty() const = 0;
    virtual size_t size() const = 0;

    virtual void clear() = 0;
};
