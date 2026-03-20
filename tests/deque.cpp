#include "../src/arraydeque.h"
#include <iostream>
#include <string>

void test_basic_operations()
{
    std::cout << "=== Testing Basic Operations ===" << std::endl;
    ArrayDeque<int> dq;

    std::cout << "Empty: " << dq.empty() << " (expected: 1)" << std::endl;

    dq.pushBack(10);
    dq.pushFront(20);
    dq.pushBack(30);
    std::cout << "Front: " << dq.front() << " (expected 20)" << std::endl;
    std::cout << "Back: " << dq.back() << " (expected 30)" << std::endl;

    dq.add(1, 15); 
    std::cout << "Added 15 at index 1. Size: " << dq.size() << " (expected: 4)" << std::endl;
    std::cout << "Element at index 1: " << dq.get(1) << " (expected: 15)" << std::endl;
}

void test_pop_operations()
{
    std::cout << "\n=== Testing Pop/Remove Operations ===" << std::endl;
    ArrayDeque<std::string> dq;

    dq.pushBack("apple");
    dq.pushBack("banana");
    dq.pushBack("cherry");

    std::cout << "Popped Front: " << dq.popFront() << " (expected: apple)" << std::endl;
    
    dq.add(1, "date"); 
    std::string removed = dq.remove(0); 
    std::cout << "Removed index 0: " << removed << " (expected: banana)" << std::endl;
    std::cout << "Current Front: " << dq.front() << " (expected: date)" << std::endl;
}

void test_resize()
{
    std::cout << "\n=== Testing Resize Operations ===" << std::endl;
    ArrayDeque<int> dq;

    for (int i = 0; i < 12; i++)
    {
        dq.pushBack(i * 10);
        std::cout << "Added " << (i * 10) << ", size: " << dq.size()
                  << ", array length: " << dq.a.length << std::endl;
    }

    for (int i = 0; i < 9; i++)
    {
        dq.popFront();
        std::cout << "Popped, size: " << dq.size() 
                  << ", array length: " << dq.a.length << std::endl;
    }
}

void test_mixed()
{
    std::cout << "\n=== Testing Mixed Order ===" << std::endl;
    ArrayDeque<int> dq;

    dq.pushFront(1);
    dq.pushBack(2);
    dq.pushFront(3);
    dq.pushBack(4);
    // Result should be: 3, 1, 2, 4

    std::cout << dq.popFront() << " (expected 3)" << std::endl;
    std::cout << dq.popBack() << " (expected 4)" << std::endl;
    std::cout << dq.popFront() << " (expected 1)" << std::endl;
    std::cout << dq.popBack() << " (expected 2)" << std::endl;
}

int main()
{
    try {
        test_basic_operations();
        test_pop_operations();
        test_resize();
        test_mixed();
        std::cout << "\n=== All combined tests completed successfully! ===" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}