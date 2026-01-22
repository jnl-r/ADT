#include "array.h"
#include <cassert>
#include <algorithm>

template <class T>
class ArrayStack : public List<T>
{
public:
    array<T> a;
    int n;

    ArrayStack() : a(1), n(0) {}

    int size()
    {
        return n;
    }

    T get(int i)
    {
        assert(i >= 0 && i < n);
        return a[i];
    }

    T set(int i, T x)
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

    void add(int i, T x)
    {
        if ((n + 1) > a.length)
            resize();
        for (int j = n; j > i; j--)
        {
            a[j] = a[j - 1];
        }
        a[i] = x;
        n++;
    }

    T remove(int i)
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
};