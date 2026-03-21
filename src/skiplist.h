#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include "../include/sset.h"

using namespace std;

template <typename T>
class SkipListSSet : public SSet<T>
{
private:
    struct Node
    {
        T data;
        vector<Node *> next;
        Node(const T &x, int level) : data(x),
                                      next(level + 1, nullptr) {}
    };

    Node *head;
    int n;
    int h;
    static const int MAX_LEVEL = 32;

    // manual random height generator
    int randomHeight()
    {
        int level = 0;
        while (level < MAX_LEVEL - 1 && (rand() & 1))
        {
            ++level;
        }
        return level;
    }

    vector<Node *> findPreds(const T &x)
    {
        vector<Node *> preds(h + 1, nullptr);
        Node *u = head;
        int r = h;
        while (r >= 0)
        {
            while (u->next[r] && u->next[r]->data < x)
            {
                u = u->next[r];
            }
            preds[r] = u;
            --r;
        }
        return preds;
    }

public:
    SkipListSSet() : n(0), h(0)
    {
        srand(static_cast<unsigned>(time(nullptr)));
        head = new Node(T(), MAX_LEVEL);
        for (int i = 0; i <= MAX_LEVEL; ++i)
        {
            head->next[i] = nullptr;
        }
    }

    ~SkipListSSet() override
    {
        clear();
        delete head;
    }

    bool add(const T &x) override
    {
        vector<Node *> preds = findPreds(x);

        if (preds[0]->next[0] && preds[0]->next[0]->data == x)
        {
            return false;
        }
        int level = randomHeight();
        if (level > h)
        {
            preds.resize(level + 1, head);
            for (int i = h + 1; i <= level; ++i)
            {
                preds[i] = head;
            }
            h = level;
        }
        Node *newNode = new Node(x, level);
        for (int i = 0; i <= level; ++i)
        {
            newNode->next[i] = preds[i]->next[i];
            preds[i]->next[i] = newNode;
        }
        ++n;
        return true;
    }

    bool remove(const T &x) override
    {
        vector<Node *> preds = findPreds(x);
        Node *target = preds[0]->next[0];
        if (!target || target->data != x)
        {
            return false;
        }
        int level = static_cast<int>(target->next.size()) - 1;
        for (int i = 0; i <= level; ++i)
        {
            preds[i]->next[i] = target->next[i];
        }

        while (h > 0 && head->next[h] == nullptr)
        {
            --h;
        }
        delete target; // shrink height if needed
        --n;
        return true;
    }

    bool contains(const T &x) const override
    {
        Node *u = head;
        int r = h;
        while (r >= 0)
        {
            while (u->next[r] && u->next[r]->data < x)
            {
                u = u->next[r];
            }
            --r;
        }
        u = u->next[0];
        return u && u->data == x;
    }

    size_t size() const override
    {
        return n;
    }

    void clear() override
    {
        Node *curr = head->next[0];
        while (curr)
        {
            Node *next = curr->next[0];
            delete curr;
            curr = next;
        }
        // Reset head pointers
        for (int i = 0; i <= h; ++i)
        {
            head->next[i] = nullptr;
        }
        n = 0;
        h = 0;
    }

    vector<T> toVector() const
    {
        vector<T> result;
        Node *curr = head->next[0];
        while (curr)
        {
            result.push_back(curr->data);
            curr = curr->next[0];
        }
        return result;
    }
};