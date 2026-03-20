#include "../src/meldableheap.h"
#include <iostream>

int main() {
    MeldableHeap<int> pq;

    std::cout << "=== Meldable Heap Test ===\n";

    pq.push(5);
    pq.push(2);
    pq.push(8);
    pq.push(1);

    std::cout << "Top (expected 1): " << pq.top() << "\n";

    while (!pq.empty()) {
        std::cout << pq.pop() << " ";
    }
    std::cout << "\nExpected order: 1 2 5 8\n";

    return 0;
}