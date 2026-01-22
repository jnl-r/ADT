#pragma once
#include <string>
#include <sstream>
#include "arraystack.h"
#include "deque.h"
#include "list.h"

template <typename T>
class DualArrayDeque : public Deque<T>, public List<T>
{
private:
    ArrayStack<T> front;
    ArrayStack<T> back;

    void balance()
    {
        size_t total = front.size() + back.size();
        if (total == 0)
            return;

        size_t target_front = (total + 1) / 2;

        ArrayStack<T> temp;

        // Get elements from front (reversed)
        for (size_t i = front.size(); i > 0; i--)
            temp.add(temp.size(), front.get(i - 1));

        // Get elements from back (normal)
        for (size_t i = 0; i < back.size(); i++)
            temp.add(temp.size(), back.get(i));

        while (front.size() > 0)
            front.remove(0);
        while (back.size() > 0)
            back.remove(0);

        // Rebuild front with first target_front elements (in reverse)
        for (size_t i = 0; i < target_front; i++)
            front.add(front.size(), temp.get(target_front - 1 - i));

        // Rebuild back with remaining elements
        for (size_t i = target_front; i < total; i++)
            back.add(back.size(), temp.get(i));
    }

public:
    DualArrayDeque() {}

    void addFirst(const T &x) override
    {
        front.add(front.size(), x);
        if (front.size() >= 3 * (back.size() + 1))
            balance();
    }

    void addLast(const T &x) override
    {
        back.add(back.size(), x);
        if (back.size() >= 3 * (front.size() + 1))
            balance();
    }

    T removeFirst() override
    {
        if (front.size() == 0 && back.size() == 0)
            throw std::out_of_range("Deque is empty");

        if (front.size() == 0)
            balance();

        T x = front.remove(front.size() - 1);
        if (size() > 1 && (front.size() == 0 || front.size() < back.size() / 3))
            balance();
        return x;
    }

    T removeLast() override
    {
        if (front.size() == 0 && back.size() == 0)
            throw std::out_of_range("Deque is empty");

        if (back.size() == 0)
            balance();

        T x = back.remove(back.size() - 1);
        if (front.size() > 1 && back.size() < front.size() / 3)
            balance();
        return x;
    }

    const T peekFirst() const override
    {
        if (front.size() == 0 && back.size() == 0)
            throw std::out_of_range("Deque is empty");

        if (front.size() > 0)
            return front.get(front.size() - 1);
        else
            return back.get(0);
    }

    const T peekLast() const override
    {
        if (front.size() == 0 && back.size() == 0)
            throw std::out_of_range("Deque is empty");

        if (back.size() > 0)
            return back.get(back.size() - 1);
        else
            return front.get(0);
    }

    bool isEmpty() const override
    {
        return front.size() == 0 && back.size() == 0;
    }

    void clear() override
    {
        while (front.size() > 0)
            front.remove(0);
        while (back.size() > 0)
            back.remove(0);
    }

    size_t size() const override
    {
        return front.size() + back.size();
    }

    void add(const size_t i, const T &x) override
    {
        if (i > size())
            throw std::out_of_range("Index out of range");

        if (i < front.size())
        {
            // FIX: correct insertion index
            front.add(front.size() - i, x);
        }
        else
        {
            back.add(i - front.size(), x);
        }

        if (front.size() > 3 * (back.size() + 1) || back.size() > 3 * (front.size() + 1))
            balance();
    }

    T remove(const size_t i) override
    {
        if (i >= size())
            throw std::out_of_range("Index out of range");

        T x;
        if (i < front.size())
        {
            x = front.remove(front.size() - i - 1);
        }
        else
        {
            x = back.remove(i - front.size());
        }

        if (size() > 1 && (front.size() < back.size() / 3 || back.size() < front.size() / 3))
            balance();
        return x;
    }

    T get(const size_t i) const override
    {
        if (i >= size())
            throw std::out_of_range("Index out of range");

        if (i < front.size())
        {
            return front.get(front.size() - i - 1);
        }
        else
        {
            return back.get(i - front.size());
        }
    }

    T set(const size_t i, const T &x) override
    {
        if (i >= size())
            throw std::out_of_range("Index out of range");

        if (i < front.size())
        {
            return front.set(front.size() - i - 1, x);
        }
        else
        {
            return back.set(i - front.size(), x);
        }
    }

    std::string state() const
    {
        std::ostringstream oss;

        // Print front stack in reverse order
        for (size_t i = front.size(); i > 0; i--)
        {
            oss << front.get(i - 1);
            if (i > 1)
                oss << " ";
        }

        oss << " | ";

        // Print back stack in forward order
        for (size_t i = 0; i < back.size(); i++)
        {
            oss << back.get(i);
            if (i < back.size() - 1)
                oss << " ";
        }

        oss << "\n";
        return oss.str();
    }
};
