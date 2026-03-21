#pragma once
#include "../include/sset.h"
#include <vector>
#include <stack>
#include <algorithm>

template <typename T>
class RedBlackTree : public SSet<T>
{
private:
    enum Color { RED, BLACK };

    struct Node {
        T value;
        Color color;
        Node *left, *right, *parent;

        Node(const T& v)
            : value(v), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;
    size_t n;

    void rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right) y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node* z) {
        while (z != root && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateRight(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void fixDelete(Node* x, Node* xParent) {
        while (x != root && (!x || x->color == BLACK)) {
            if (x == xParent->left) {
                Node* w = xParent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    xParent->color = RED;
                    rotateLeft(xParent);
                    w = xParent->right;
                }
                if ((!w->left || w->left->color == BLACK) && 
                    (!w->right || w->right->color == BLACK)) {
                    w->color = RED;
                    x = xParent;
                    xParent = x->parent;
                } else {
                    if (!w->right || w->right->color == BLACK) {
                        if (w->left) w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(w);
                        w = xParent->right;
                    }
                    w->color = xParent->color;
                    xParent->color = BLACK;
                    if (w->right) w->right->color = BLACK;
                    rotateLeft(xParent);
                    x = root;
                }
            } else {
                Node* w = xParent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    xParent->color = RED;
                    rotateRight(xParent);
                    w = xParent->left;
                }
                if ((!w->right || w->right->color == BLACK) && 
                    (!w->left || w->left->color == BLACK)) {
                    w->color = RED;
                    x = xParent;
                    xParent = x->parent;
                } else {
                    if (!w->left || w->left->color == BLACK) {
                        if (w->right) w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(w);
                        w = xParent->left;
                    }
                    w->color = xParent->color;
                    xParent->color = BLACK;
                    if (w->left) w->left->color = BLACK;
                    rotateRight(xParent);
                    x = root;
                }
            }
        }
        if (x) x->color = BLACK;
    }

    void clear(Node* u) {
    if (!u) return;
    std::vector<Node*> stack;
    stack.push_back(u);
    while (!stack.empty()) {
        Node* curr = stack.back();
        stack.pop_back();
        if (curr->left) stack.push_back(curr->left);
        if (curr->right) stack.push_back(curr->right);
        delete curr;
    }
}

public:
    RedBlackTree() : root(nullptr), n(0) {}
    ~RedBlackTree() { clear(); }

    RedBlackTree(const RedBlackTree&) = delete;
    RedBlackTree& operator=(const RedBlackTree&) = delete;

    bool add(const T& x) override {
        Node *y = nullptr, *cur = root;
        while (cur) {
            y = cur;
            if (x < cur->value) cur = cur->left;
            else if (x > cur->value) cur = cur->right;
            else return false;
        }
        Node* z = new Node(x);
        z->parent = y;
        if (!y) root = z;
        else if (x < y->value) y->left = z;
        else y->right = z;
        fixInsert(z);
        n++;
        return true;
    }

    bool remove(const T& x) override {
        Node *z = root;
        while (z && z->value != x) {
            if (x < z->value) z = z->left;
            else z = z->right;
        }
        if (!z) return false;

        Node *x_node, *y = z;
        Color y_original_color = y->color;
        Node* x_parent;

        if (!z->left) {
            x_node = z->right;
            x_parent = z->parent;
            if (!z->parent) root = z->right;
            else if (z == z->parent->left) z->parent->left = z->right;
            else z->parent->right = z->right;
            if (z->right) z->right->parent = z->parent;
        } else if (!z->right) {
            x_node = z->left;
            x_parent = z->parent;
            if (!z->parent) root = z->left;
            else if (z == z->parent->left) z->parent->left = z->left;
            else z->parent->right = z->left;
            if (z->left) z->left->parent = z->parent;
        } else {
            y = z->right;
            while (y->left) y = y->left;
            y_original_color = y->color;
            x_node = y->right;
            if (y->parent == z) {
                x_parent = y;
            } else {
                x_parent = y->parent;
                x_parent->left = y->right;
                if (y->right) y->right->parent = x_parent;
                y->right = z->right;
                y->right->parent = y;
            }
            if (!z->parent) root = y;
            else if (z == z->parent->left) z->parent->left = y;
            else z->parent->right = y;
            y->parent = z->parent;
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == BLACK) fixDelete(x_node, x_parent);
        n--;
        return true;
    }

    bool contains(const T& x) const override {
        Node* cur = root;
        while (cur) {
            if (x < cur->value) cur = cur->left;
            else if (x > cur->value) cur = cur->right;
            else return true;
        }
        return false;
    }

    size_t size() const override { return n; }
    void clear() override { clear(root); root = nullptr; n = 0; }
};