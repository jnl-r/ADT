#pragma once
#include <cstdlib>   
#include <ctime>
#include <utility> 
#include <stdexcept> // Added for runtime_error
#include "../include/prioqueue.h"

template <typename T>
class MeldableHeap : public PriorityQueue<T> {
private:
    struct Node {
        T value;
        Node *left, *right;
        Node(const T& v) : value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;
    size_t n;

    Node* merge(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        if (h2->value < h1->value) {
            std::swap(h1, h2);
        }

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
        if (!root) throw std::runtime_error("Heap is empty");

        T minVal = root->value;
        Node* oldRoot = root;

        root = merge(root->left, root->right);
        delete oldRoot;
        n--;

        return minVal;
    }

    const T& top() const override {
        if (!root) throw std::runtime_error("Heap is empty");
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
        MeldableHeap<T>* o = dynamic_cast<MeldableHeap<T>*>(&other);
        if (!o) return;

        root = merge(root, o->root);
        n += o->n;

        o->root = nullptr;
        o->n = 0;
    }
};