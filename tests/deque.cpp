#include "../src/arraydeque.h"
#include <iostream>
#include <string>

int main() {
    ArrayDeque<int> dq;
    std::string cmd;
    int val, idx;

    std::cout << "\n\n\n################################################################################\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ARRAY DEQUE TESTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "Commands:" << std::endl;
    std::cout << "  pushf <val>            pushFront: add to the very beginning" << std::endl;
    std::cout << "  pushb <val>            pushBack: add to the very end" << std::endl;
    std::cout << "  add <idx> <val>        add at specific index (shifts elements)" << std::endl;
    std::cout << "  popf                   popFront: remove from the beginning" << std::endl;
    std::cout << "  popb                   popBack: remove from the end" << std::endl;
    std::cout << "  remove <idx>           remove at specific index" << std::endl;
    std::cout << "  get <idx>              peek at value at index" << std::endl;
    std::cout << "  set <idx> <val>        replace value at index" << std::endl;
    std::cout << "  size                   print current size and array capacity" << std::endl;
    std::cout << "  clear                  remove all elements" << std::endl;
    std::cout << "  quit                   exit program" << std::endl;
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "################################################################################\n";

    while (std::cout << "> " && std::cin >> cmd && cmd != "quit" && cmd != "exit") {
        try {
            if (cmd == "pushf") {
                if (std::cin >> val) { dq.pushFront(val); std::cout << "Pushed front: " << val << "\n"; }
            } 
            else if (cmd == "pushb") {
                if (std::cin >> val) { dq.pushBack(val); std::cout << "Pushed back: " << val << "\n"; }
            }
            else if (cmd == "add") {
                if (std::cin >> idx >> val) { dq.add(idx, val); std::cout << "Added " << val << " at index " << idx << "\n"; }
            }
            else if (cmd == "popf") {
                std::cout << "Popped front: " << dq.popFront() << "\n";
            }
            else if (cmd == "popb") {
                std::cout << "Popped back: " << dq.popBack() << "\n";
            }
            else if (cmd == "remove") {
                if (std::cin >> idx) std::cout << "Removed from index " << idx << ": " << dq.remove(idx) << "\n";
            }
            else if (cmd == "get") {
                if (std::cin >> idx) std::cout << "Value at [" << idx << "]: " << dq.get(idx) << "\n";
            }
            else if (cmd == "set") {
                if (std::cin >> idx >> val) {
                    int old = dq.set(idx, val);
                    std::cout << "Set [" << idx << "] to " << val << " (was " << old << ")\n";
                }
            }
            else if (cmd == "size") {
                // Assuming your backing array is named 'a' with a '.length' property
                std::cout << "Size: " << dq.size() << "\n";
            }
            else if (cmd == "clear") {
                dq.clear();
                std::cout << "Deque cleared\n";
            }
            else {
                std::cout << "Unknown command\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}