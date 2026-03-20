#include "../src/arraydeque.h"
#include <iostream>
#include <string>

void test_basic_operations()
{
    std::cout << "- Basic Operations -\n";

    ArrayDeque<int> dq;

    std::cout << "Empty: " << dq.empty() << " (expected 1)\n";

    dq.pushBack(10);
    dq.pushFront(20);
    dq.pushBack(30);

    std::cout << "Front: " << dq.front() << " (expected 20)\n";
    std::cout << "Back: " << dq.back() << " (expected 30)\n";
    std::cout << "Size: " << dq.size() << " (expected 3)\n";
}

void test_pop_operations()
{
    std::cout << "\n- Pop Operations -\n";

    ArrayDeque<std::string> dq;

    dq.pushBack("apple");
    dq.pushBack("banana");
    dq.pushBack("cherry");

    std::cout << dq.popFront() << " (expected apple)\n";
    std::cout << dq.popBack() << " (expected cherry)\n";
    std::cout << dq.popFront() << " (expected banana)\n";

    std::cout << "Empty: " << dq.empty() << " (expected 1)\n";
}

void test_resize()
{
    std::cout << "\n- Resize Test -\n";

    ArrayDeque<int> dq;

    for (int i = 0; i < 20; i++) {
        dq.pushBack(i);
    }

    std::cout << "Size after insert: " << dq.size() << " (expected 20)\n";

    for (int i = 0; i < 15; i++) {
        dq.popFront();
    }

    std::cout << "Size after removals: " << dq.size() << " (expected 5)\n";
}

void test_mixed()
{
    std::cout << "\n- Mixed Operations -\n";

    ArrayDeque<int> dq;

    dq.pushFront(1);
    dq.pushBack(2);
    dq.pushFront(3);
    dq.pushBack(4);

    // should be: 3,1,2,4

    std::cout << dq.popFront() << " (expected 3)\n";
    std::cout << dq.popBack() << " (expected 4)\n";
    std::cout << dq.popFront() << " (expected 1)\n";
    std::cout << dq.popBack() << " (expected 2)\n";
}

int main()
{
    test_basic_operations();
    test_pop_operations();
    test_resize();
    test_mixed();

    std::cout << "\nAll tests done.\n";
    return 0;
}