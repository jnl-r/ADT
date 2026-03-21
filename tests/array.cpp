#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "../src/arraystack.h"

using namespace std;

int main()
{
    ArrayStack<int> st;
    string line;

    cout << "\n\n\n################################################################################\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~ ARRAYSTACK (FILO STACK) TESTS ~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "Commands:" << endl;
    cout << "  push <value>                 add value to the top of the stack" << endl;
    cout << "  pop                          remove and print value from the top" << endl;
    cout << "  size                         print number of elements" << endl;
    cout << "  quit                         exit program" << endl;
    cout << "--------------------------------------------------------------------------------\n";
    cout << "################################################################################\n";

    cout << "> ";
    while (getline(cin, line))
    {
        if (line.empty()) {
            cout << "> ";
            continue;
        }

        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "quit" || cmd == "exit") {
            break;
        }
        else if (cmd == "size") {
            cout << st.size() << endl;
        }
        else if (cmd == "push") {
            int x;
            if (!(iss >> x)) {
                cout << "Usage: push <value>" << endl;
            } else {
                st.push(x);
                cout << "Pushed " << x << endl;
            }
        }
        else if (cmd == "pop") {
            try {
                if (st.size() == 0) {
                    cout << "Stack is empty." << endl;
                } else {
                    cout << "Popped: " << st.pop() << endl;
                }
            } catch (...) {
                cout << "Error: Stack is empty." << endl;
            }
        }
        else {
            cout << "Unknown command." << endl;
        }
        cout << "> ";
    }
    return 0;
}