#pragma once
#include <cstddef>

template <typename T>
struct USet {
    virtual ~USet() {}
    
    virtual bool add(const T& x) = 0;    
    virtual bool remove(const T& x) = 0; 
    virtual bool find(const T& x) const = 0; 
    virtual size_t size() const = 0;
};