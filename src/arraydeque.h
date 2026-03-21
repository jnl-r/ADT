#pragma once
#include "../include/array.h"
#include "../include/list.h"
#include "../include/deque.h"
#include <algorithm>
#include <cstddef>

template <typename T>
class ArrayDeque : public Deque<T>, public List<T>
{
public: // <-- Changed to public so tests/deque.cpp can read a.length!
    array<T> a;
    int j;
    int n;
    const static size_t MIN_CAPACITY = 10;

    void resize() {
        size_t new_len = std::max(MIN_CAPACITY, 2 * a.length);

        array<T> b(new_len);
        for (int k = 0; k < n; k++) {
            b[k] = a[(j + k) % a.length];
        }
        a = b;
        j = 0;
    }

    ArrayDeque() : a(MIN_CAPACITY), j(0), n(0) {}

    void add(const size_t i, const T& x) override {
        if (i > (size_t)n) return;

        if ((size_t)n + 1 > a.length) resize();

        if (i < (size_t)n / 2) {
            j = (j == 0) ? a.length - 1 : j - 1;
            // FIXED LOOP: Shift elements to the left correctly
            for (int k = 0; k < (int)i; k++) {
                a[(j + k) % a.length] = a[(j + k + 1) % a.length];
            }
        } else {
            // Shift elements to the right
            for (int k = n; k > (int)i; k--) {
                a[(j + k) % a.length] = a[(j + k - 1) % a.length];
            }
        }

        a[(j + i) % a.length] = x;
        n++;
    }

    T remove(const size_t i) override {
        if (i >= (size_t)n) return T();

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

        if (a.length > MIN_CAPACITY && (size_t)n < a.length / 4) {
            size_t new_len = std::max(MIN_CAPACITY, a.length / 2);

            array<T> b(new_len);
            for (int k = 0; k < n; k++) {
                b[k] = a[(j + k) % a.length];
            }
            a = b;
            j = 0;
        }

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

    size_t size() const override {
        return n;
    }

    void pushFront(const T& value) override {
        add(0, value);
    }

    void pushBack(const T& value) override {
        add(n, value);
    }

    T popFront() override {
        if (empty()) return T();
        return remove(0);
    }

    T popBack() override {
        if (empty()) return T();
        return remove(n - 1);
    }

    const T& front() const override {
        return a[j];
    }

    const T& back() const override {
        return a[(j + n - 1) % a.length];
    }

    bool empty() const override {
        return n == 0;
    }

    void clear() override {
        j = 0;
        n = 0;
    }
};

template <typename T>
const size_t ArrayDeque<T>::MIN_CAPACITY;