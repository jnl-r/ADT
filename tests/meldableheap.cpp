#include "../src/meldableheap.h"
#include <iostream>
#include <string>

int main() {
    MeldableHeap<int> pq;
    std::string cmd;
    int val;

    std::cout << "\n\n\n################################################################################\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~ MELDABLE HEAP TESTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "Commands:" << std::endl;
    std::cout << "  push <value>                     add value to the heap" << std::endl;
    std::cout << "  pop                              remove and return the minimum value" << std::endl;
    std::cout << "  top                              view the minimum value without removing" << std::endl;
    std::cout << "  size                             print number of elements" << std::endl;
    std::cout << "  empty                            check if heap is empty" << std::endl;
    std::cout << "  clear                            remove all elements from heap" << std::endl;
    std::cout << "  quit                             exit program" << std::endl;
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "################################################################################\n";

    while (std::cout << "> " && std::cin >> cmd && cmd != "quit" && cmd != "exit") {
        if (cmd == "push") {
            if (std::cin >> val) {
                pq.push(val);
                std::cout << "Pushed " << val << "\n";
            }
        } 
        else if (cmd == "pop") {
            try {
                if (pq.empty()) {
                    std::cout << "Error: Heap is empty\n";
                } else {
                    std::cout << "Popped: " << pq.pop() << "\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        } 
        else if (cmd == "top") {
            try {
                std::cout << "Top: " << pq.top() << "\n";
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        } 
        else if (cmd == "size") {
            std::cout << "Size: " << pq.size() << "\n";
        } 
        else if (cmd == "empty") {
            std::cout << (pq.empty() ? "Yes, heap is empty" : "No, heap has data") << "\n";
        }
        else if (cmd == "clear") {
            pq.clear();
            std::cout << "Heap cleared\n";
        }
        else {
            std::cout << "Unknown command\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }

    return 0;
}