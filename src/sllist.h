#pragma once
#include "../include/queue.h"
#include <cstddef>
#include <stdexcept>

template <typename T>
class SLList : public Queue<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {} 
    };

    Node* head; 
    Node* tail; 
    size_t n;   

public:
    SLList() : head(nullptr), tail(nullptr), n(0) {}

    ~SLList() override {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void enqueue(const T& x) override {
        Node* newNode = new Node(x);
        
        if (n == 0) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
        n++;
    }

    T dequeue() override {
        if (n == 0) {
            throw std::out_of_range("the queue is empty");
        }
        
        T x = head->data;     
        Node* temp = head;    
        
        head = head->next;    
        delete temp;          
        n--;

        if (n == 0) {
            tail = nullptr;
        }
        
        return x;
    }

    size_t size() const override {
        return n;
    }
};