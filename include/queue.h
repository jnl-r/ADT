#pragma once
#include <cstddef>

template <typename T>
struct Queue {
    virtual ~Queue() {}
    
    virtual void enqueue(const T& x) = 0; 
    virtual T dequeue() = 0;              // Remove from front
    virtual size_t size() const = 0;
};