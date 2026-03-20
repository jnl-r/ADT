#include "../src/arraydeque.h"
#include <iostream>
#include <string>

void test_basic_operations()
{
    std::cout << "=== Testing Basic Operations ===" << std::endl;
    ArrayDeque<int> dq;

    std::cout << "Empty: " << dq.empty() << " (expected: 1)" << std::endl;
    std::cout << "Size: " << dq.size() << " (expected: 0)" << std::endl;

    dq.add(0, 10);
    std::cout << "Added 10 at index 0" << std::endl;
    std::cout << "Empty: " << dq.empty() << " (expected: 0)" << std::endl;
    std::cout << "Size: " << dq.size() << " (expected: 1)" << std::endl;

    dq.add(0, 20); 
    std::cout << "Added 20 at index 0" << std::endl;

    dq.add(2, 30); 
    std::cout << "Added 30 at index 2" << std::endl;

    dq.add(1, 15); 
    std::cout << "Added 15 at index 1" << std::endl;

    std::cout << "Current size: " << dq.size() << " (expected: 4)" << std::endl;
}

void test_remove_operations()
{
    std::cout << "\n=== Testing Remove Operations ===" << std::endl;
    ArrayDeque<std::string> dq;

    dq.add(0, "apple");
    dq.add(1, "banana");
    dq.add(2, "cherry");
    dq.add(3, "date");

    std::cout << "Initial size: " << dq.size() << std::endl;

    std::string removed = dq.remove(1);
    std::cout << "Removed: " << removed << " (expected: banana)" << std::endl;
    std::cout << "Size after removal: " << dq.size() << " (expected: 3)" << std::endl;

    removed = dq.remove(0);
    std::cout << "Removed: " << removed << " (expected: apple)" << std::endl;

    removed = dq.remove(1); 
    std::cout << "Removed: " << removed << " (expected: date)" << std::endl;

    std::cout << "Final size: " << dq.size() << " (expected: 1)" << std::endl;
}

void test_resize_operations()
{
    std::cout << "\n=== Testing Resize Operations ===" << std::endl;
    ArrayDeque<int> dq;

    for (int i = 0; i < 10; i++)
    {
        dq.add(i, i * 10);
        std::cout << "Added " << (i * 10) << ", size: " << dq.size()
                  << ", array length: " << dq.a.length << std::endl;
    }

    for (int i = 0; i < 7; i++)
    {
        int removed = dq.remove(0);
        std::cout << "Removed " << removed << ", size: " << dq.size()
                  << ", array length: " << dq.a.length << std::endl;
    }
}

void test_edge_cases()
{
    std::cout << "\n=== Testing Edge Cases ===" << std::endl;
    ArrayDeque<double> dq;

    dq.add(0, 1.1);
    dq.add(0, 2.2); 
    dq.add(2, 3.3); 
    dq.add(1, 4.4); 

    std::cout << "After mixed additions - size: " << dq.size() << std::endl;

    while (dq.size() > 0)
    {
        double val = dq.remove(0);
        std::cout << "Removed: " << val << std::endl;
    }

    std::cout << "Final empty: " << dq.empty() << " (expected: 1)" << std::endl;
}

int main()
{
    try
    {
        test_basic_operations();
        test_remove_operations();
        test_resize_operations();
        test_edge_cases();

        std::cout << "\n=== All tests completed successfully! ===" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}