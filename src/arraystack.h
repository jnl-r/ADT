#pragma once
#include "../include/array.h"
#include "../include/list.h"
#include "../include/stack.h" 
#include <cassert>
#include <algorithm>

template <class T>
class ArrayStack : public List<T>, public Stack<T> 
{
public:
    array<T> a;
    int n;

    ArrayStack() : a(1), n(0) {}

    size_t size() const override
    {
        return n;
    }

    T get(const size_t i) const override 
    {
        assert(i >= 0 && i < (size_t)n);
        return a[i];
    }

    T set(const size_t i, const T& x) override
    {
        T y = a[i];
        a[i] = x;
        return y;
    }

    void resize()
    {
        array<T> b(std::max(2 * n, 1));
        for (int i = 0; i < n; i++)
        {
            b[i] = a[i];
        }
        a = b;
    }

    void add(const size_t i, const T& x) override
    {
        if ((n + 1) > a.length)
            resize();
        for (int j = n; j > (int)i; j--)
        {
            a[j] = a[j - 1];
        }
        a[i] = x;
        n++;
    }

    T remove(const size_t i) override
    {
        T x = a[i];
        for (int j = i; j < n - 1; j++)
        {
            a[j] = a[j + 1];
        }
        n--;
        if (a.length >= 3 * n)
            resize();
        return x;
    }

    void push(const T& x) override
    {
        add(n, x); 
    }

    T pop() override
    {
        assert(n > 0); 
        return remove(n - 1); 
    }
};