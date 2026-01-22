#include "arraydeque.h"
#include <iostream>
#include <string>

void test_basic_operations()
{
    std::cout << "=== Testing Basic Operations ===" << std::endl;
    ArrayDeque<int> deque;

    // Test empty deque
    std::cout << "Empty: " << deque.isEmpty() << " (expected: 1)" << std::endl;
    std::cout << "Size: " << deque.size() << " (expected: 0)" << std::endl;

    // Add elements
    deque.add(0, 10);
    std::cout << "Added 10 at index 0" << std::endl;
    std::cout << "Empty: " << deque.isEmpty() << " (expected: 0)" << std::endl;
    std::cout << "Size: " << deque.size() << " (expected: 1)" << std::endl;

    deque.add(0, 20); // front
    std::cout << "Added 20 at index 0" << std::endl;

    deque.add(2, 30); // at end
    std::cout << "Added 30 at index 2" << std::endl;

    deque.add(1, 15); // in middle
    std::cout << "Added 15 at index 1" << std::endl;

    // Expected: 20, 15, 10, 30
    std::cout << "Current size: " << deque.size() << " (expected: 4)" << std::endl;
}

void test_remove_operations()
{
    std::cout << "\n=== Testing Remove Operations ===" << std::endl;
    ArrayDeque<std::string> deque;

    // Add some elements
    deque.add(0, "apple");
    deque.add(1, "banana");
    deque.add(2, "cherry");
    deque.add(3, "date");

    std::cout << "Initial size: " << deque.size() << std::endl;

    // Remove from middle
    std::string removed = deque.remove(1);
    std::cout << "Removed: " << removed << " (expected: banana)" << std::endl;
    std::cout << "Size after removal: " << deque.size() << " (expected: 3)" << std::endl;

    // Remove from front
    removed = deque.remove(0);
    std::cout << "Removed: " << removed << " (expected: apple)" << std::endl;

    // Remove from end
    removed = deque.remove(1); // Now indices are 0:cherry, 1:date
    std::cout << "Removed: " << removed << " (expected: date)" << std::endl;

    std::cout << "Final size: " << deque.size() << " (expected: 1)" << std::endl;
}

void test_resize_operations()
{
    std::cout << "\n=== Testing Resize Operations ===" << std::endl;
    ArrayDeque<int> deque;

    // Add many elements to trigger resize
    for (int i = 0; i < 10; i++)
    {
        deque.add(i, i * 10);
        std::cout << "Added " << (i * 10) << ", size: " << deque.size()
                  << ", array length: " << deque.a.length << std::endl;
    }

    // Remove elements to trigger downsize
    for (int i = 0; i < 7; i++)
    {
        int removed = deque.remove(0);
        std::cout << "Removed " << removed << ", size: " << deque.size()
                  << ", array length: " << deque.a.length << std::endl;
    }
}

void test_edge_cases()
{
    std::cout << "\n=== Testing Edge Cases ===" << std::endl;
    ArrayDeque<double> deque;

    // Test adding/removing at various positions
    deque.add(0, 1.1);
    deque.add(0, 2.2); // Add to front of existing element
    deque.add(2, 3.3); // Add to end
    deque.add(1, 4.4); // Add to middle

    std::cout << "After mixed additions - size: " << deque.size() << std::endl;

    // Test wrap-around behavior
    while (deque.size() > 0)
    {
        double val = deque.remove(0);
        std::cout << "Removed: " << val << std::endl;
    }

    std::cout << "Final empty: " << deque.isEmpty() << " (expected: 1)" << std::endl;
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