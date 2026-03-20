#pragma once
#include <cstddef>

template <typename T>
struct Stack {
    virtual ~Stack() {}
    
    virtual void push(const T& x) = 0;
    virtual T pop() = 0;
    virtual size_t size() const = 0;
};