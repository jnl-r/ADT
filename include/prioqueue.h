#pragma once
#include <cstddef>

template <typename T>
class PriorityQueue {
public:
    virtual ~PriorityQueue() {}

    virtual void push(const T& value) = 0;
    virtual T pop() = 0;
    virtual const T& top() const = 0;

    virtual bool empty() const = 0;
    virtual size_t size() const = 0;

    virtual void clear() = 0;

    virtual void merge(PriorityQueue<T>& other) = 0; //check if oki ra ba 
};