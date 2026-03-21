#pragma once
#include "../include/array.h"
#include "../include/list.h"
#include "../include/deque.h"
#include <algorithm>
#include <cstddef>

template <typename T>
class ArrayDeque : public Deque<T>, public List<T>
{
private:
    void resize()
    {
        array<T> b(std::max(2 * n, 1));
        for (int k = 0; k < n; k++)
        {
            b[k] = a[(j + k) % a.length];
        }
        a = b;
        j = 0;
    }

public:
    array<T> a;
    int j;
    int n;

    ArrayDeque() : a(10), j(0), n(0) {}

    // From deque.h
    void addFirst(const T &x) override
    {
        if (n + 1 > a.length)
            resize();

        j = (j == 0) ? a.length - 1 : j - 1;
        a[j] = x;
        n++;
    }

    void addLast(const T &x) override
    {
        if (n + 1 > a.length)
            resize();

        a[(j + n) % a.length] = x;
        n++;
    }

    T removeFirst() override
    {
        if (n == 0)
            throw std::runtime_error("Empty deque");

        T x = a[j];
        j = (j + 1) % a.length;
        n--;

        if (a.length >= 3 * n)
            resize();
        return x;
    }

    T removeLast() override
    {
        if (n == 0)
            throw std::runtime_error("Empty deque");

        T x = a[(j + n - 1) % a.length];
        n--;

        if (a.length >= 3 * n)
            resize();
        return x;
    }

    const T peekFirst() const override
    {
        if (n == 0)
            throw std::runtime_error("Empty deque");
        return a[j];
    }

    const T peekLast() const override
    {
        if (n == 0)
            throw std::runtime_error("Empty deque");
        return a[(j + n - 1) % a.length];
    }

    bool isEmpty() const override
    {
        return n == 0;
    }

    void clear() override
    {
        n = 0;
        j = 0;
    }

    size_t size() const override
    {
        return n;
    }

    // From list.h
    void add(const size_t i, const T &x) override
    {
        if (i < 0 || i > n)
            throw std::out_of_range("Index out of bounds");
        if (n + 1 > a.length)
            resize();

        if (i < n / 2)
        {
            j = (j == 0) ? a.length - 1 : j - 1;
            for (int k = (int)i; k > 0; k--) {
                a[(j + k) % a.length] = a[(j + k - 1) % a.length];
            }
        } else {
            for (int k = n; k > (int)i; k--) {
                a[(j + k) % a.length] = a[(j + k - 1) % a.length];
            }
        }
        a[(j + i) % a.length] = x;
        n++;
    }

    T remove(const size_t i) override
    {
        if (i < 0 || i >= n)
            throw std::out_of_range("Index out of bounds");

        T x = a[(j + i) % a.length];

        if (i < (size_t)n / 2) {
            for (int k = (int)i; k > 0; k--) {
                a[(j + k) % a.length] = a[(j + k - 1) % a.length];
            }
            j = (j + 1) % a.length;
        } else {
            for (int k = (int)i; k < n - 1; k++) {
                a[(j + k) % a.length] = a[(j + k + 1) % a.length];
            }
        }

        n--;
        if (a.length >= 3 * n && a.length > 10)
            resize();
        return x;
    }

    T get(const size_t i) const override {
        if (i >= (size_t)n) return T();
        return a[(j + i) % a.length];
    }

    T set(const size_t i, const T& x) override {
        if (i >= (size_t)n) return T();
        T y = a[(j + i) % a.length];
        a[(j + i) % a.length] = x;
        return y;
    }
};