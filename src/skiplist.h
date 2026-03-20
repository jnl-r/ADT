#pragma once

#include <random>
#include <vector>
#include <limits>
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
        Node(const T &x, size_t level) : data(x),
                                         next(level + 1, nullptr) {}
    };

    Node *head;
    size_t n;
    size_t maxLevel;
    static const size_t MAX_LEVEL = 32;

    mutable mt19937 rng;
    mutable bernoulli_distribution coin;

    size_t randomLevel() const
    {
        size_t level = 0;
        while (level < MAX_LEVEL - 1 && coin(rng))
        {
            ++level;
        }
        return level;
    }

    pair<Node *, vector<Node *>> find(const T &x) const
    {
        vector<Node *> preds(maxLevel + 1, nullptr);
        Node *curr = head;
        for (int level = static_cast<int>(maxLevel); level >= 0; --level)
        {
            while (curr->next[level] && curr->next[level]->data < x)
            {
                curr = curr->next[level];
            }
            preds[level] = curr;
        }
        curr = curr->next[0];
        if (curr && curr->data == x)
        {
            return {curr, preds};
        }
        else
        {
            return {nullptr, preds};
        }
    }

public:
    SkipListSSet() : n(0), maxLevel(0), rng(random_device{}()), coin(0.5)
    {
        head = new Node(T(), MAX_LEVEL);
        for (size_t i = 0; i <= MAX_LEVEL; ++i)
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
        pair<Node *, vector<Node *>> result = find(x);
        Node *found = result.first;
        vector<Node *> &preds = result.second;

        if (found)
        {
            return false;
        }
        size_t level = randomLevel();
        if (level > maxLevel)
        {
            preds.resize(level + 1, nullptr);
            for (size_t i = maxLevel + 1; i <= level; ++i)
            {
                preds[i] = head;
            }
            maxLevel = level;
        }
        Node *newNode = new Node(x, level);
        for (size_t i = 0; i <= level; ++i)
        {
            newNode->next[i] = preds[i]->next[i];
            preds[i]->next[i] = newNode;
        }
        ++n;
        return true;
    }

    bool remove(const T &x) override
    {
        pair<Node *, vector<Node *>> result = find(x);
        Node *found = result.first;
        vector<Node *> &preds = result.second;

        if (!found)
        {
            return false;
        }
        Node *toDelete = found;
        size_t level = toDelete->next.size() - 1;
        for (size_t i = 0; i <= level; ++i)
        {
            preds[i]->next[i] = toDelete->next[i];
        }
        while (maxLevel > 0 && head->next[maxLevel] == nullptr)
        {
            --maxLevel;
        }
        delete toDelete;
        --n;
        return true;
    }

    bool contains(const T &x) const override
    {
        pair<Node *, vector<Node *>> result = find(x);
        Node *found = result.first;
        return found != nullptr;
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
        for (size_t i = 0; i <= maxLevel; ++i)
        {
            head->next[i] = nullptr;
        }
        n = 0;
        maxLevel = 0;
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