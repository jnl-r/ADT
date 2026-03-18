#pragma once
#include "../include/uset.h"
#include <functional> 
#include <cstddef>

template <typename T>
class ChainedHashTable : public USet<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node** table;    
    size_t capacity; 
    size_t n;        

    size_t hash(const T& x) const {
        return std::hash<T>{}(x) % capacity;
    }

public:
    ChainedHashTable() : capacity(10), n(0) {
        table = new Node*[capacity];
        for (size_t i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    ~ChainedHashTable() override {
        for (size_t i = 0; i < capacity; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }
        delete[] table; 
    }

    bool find(const T& x) const override {
        size_t index = hash(x);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->data == x) return true;
            current = current->next;
        }
        return false;
    }

    bool add(const T& x) override {
        if (find(x)) return false; 


        size_t index = hash(x);
        Node* newNode = new Node(x);
        
    
        newNode->next = table[index];
        table[index] = newNode;
        n++;
        return true;
    }

    bool remove(const T& x) override {
        size_t index = hash(x);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->data == x) {
                if (prev == nullptr) {
                    table[index] = current->next; 
                } else {
                    prev->next = current->next;   
                }
                delete current;
                n--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false; 
    }

    size_t size() const override {
        return n;
    }
};