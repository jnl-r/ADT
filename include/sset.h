#pragma once
#include <cstddef>

template <typename T>
class SSet
{
public:
    virtual ~SSet() = default;
    virtual bool add(const T &x) = 0;
    virtual bool remove(const T &x) = 0;
    virtual bool contains(const T &x) const = 0;
    virtual size_t size() const = 0;
    virtual void clear() = 0;
};