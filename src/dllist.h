#pragma once

#include <stdexcept>
#include "../include/list.h"

template <typename T>
class DLList : public List<T>
{
private:
    struct Node
    {
        T data;
        Node *prev;
        Node *next;
        Node(const T &value) : data(value),
                               prev(nullptr),
                               next(nullptr) {}
    };

    Node *head;
    Node *tail;
    size_t n;

    // returns pointer to node at index i but allows modification
    Node *getNode(size_t i)
    {
        if (i >= n)
            throw out_of_range("Index out of bounds");
        Node *curr;
        if (i < n / 2)
        {
            curr = head;
            for (size_t k = 0; k < i; ++k)
                curr = curr->next;
        }
        else
        {
            curr = tail;
            for (size_t k = n - 1; k > i; --k)
                curr = curr->prev;
        }
        return curr;
    }

    // returns const pointer to node at index i
    const Node *getNode(size_t i) const
    {
        if (i >= n)
            throw out_of_range("Index out of bounds");
        const Node *curr;
        if (i < n / 2)
        {
            curr = head;
            for (size_t k = 0; k < i; ++k)
                curr = curr->next;
        }
        else
        {
            curr = tail;
            for (size_t k = n - 1; k > i; --k)
                curr = curr->prev;
        }
        return curr;
    }

public:
    DLList() : head(nullptr), tail(nullptr), n(0) {}

    ~DLList() override
    {
        clear();
    }

    size_t size() const override
    {
        return n;
    }

    void clear() override
    {
        Node *curr = head;
        while (curr)
        {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
        head = nullptr;
        tail = nullptr;
        n = 0;
    }

    void add(size_t i, const T &x) override
    {
        if (i > n)
            throw out_of_range("Index out of bounds");

        Node *node = new Node(x);

        if (n == 0)
        {
            head = tail = node;
        }
        else if (i == 0)
        {
            node->next = head;
            head->prev = node;
            head = node;
        }
        else if (i == n)
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        else
        {
            Node *curr = getNode(i);
            node->prev = curr->prev;
            node->next = curr;
            curr->prev->next = node;
            curr->prev = node;
        }
        ++n;
    }

    T remove(size_t i) override
    {
        Node *curr = getNode(i);
        T value = curr->data;

        if (curr == head && curr == tail)
        {
            head = tail = nullptr;
        }
        else if (curr == head)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else if (curr == tail)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

        delete curr;
        --n;
        return value;
    }

    T get(size_t i) const override
    {
        return getNode(i)->data;
    }

    T set(size_t i, const T &x) override
    {
        Node *curr = getNode(i);
        T old = curr->data;
        curr->data = x;
        return old;
    }
};