#pragma once
#include <cstdlib>   
#include <ctime>
#include <utility> //for swap
#include "../include/prioqueue.h"

template <typename T>
class MeldableHeap : public PriorityQueue<T> {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;

        Node(const T& v) : value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;
    size_t n;

    Node* merge(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        // ensure min-heap
        if (h2->value < h1->value) {
            std::swap(h1, h2);
        }

        // randomly swap children
        if (rand() % 2) {
            std::swap(h1->left, h1->right);
        }

        h1->left = merge(h1->left, h2);
        return h1;
    }

    void deleteAll(Node* u) {
        if (!u) return;
        deleteAll(u->left);
        deleteAll(u->right);
        delete u;
    }

public:
    MeldableHeap() : root(nullptr), n(0) {
        srand(time(nullptr));
    }

    ~MeldableHeap() {
        clear();
    }

    void push(const T& value) override {
        Node* newNode = new Node(value);
        root = merge(root, newNode);
        n++;
    }

    T pop() override {
        if (!root) return T();

        T minVal = root->value;
        Node* oldRoot = root;

        root = merge(root->left, root->right);
        delete oldRoot;
        n--;

        return minVal;
    }

    const T& top() const override {
        return root->value;
    }

    bool empty() const override {
        return root == nullptr;
    }

    size_t size() const override {
        return n;
    }

    void clear() override {
        deleteAll(root);
        root = nullptr;
        n = 0;
    }

    void merge(PriorityQueue<T>& other) override {
        // downcast (safe if same type)
        MeldableHeap<T>* o = dynamic_cast<MeldableHeap<T>*>(&other);
        if (!o) return;

        root = merge(root, o->root);
        n += o->n;

        o->root = nullptr;
        o->n = 0;
    }
};