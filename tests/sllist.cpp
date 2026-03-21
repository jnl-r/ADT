#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "../src/sllist.h"

using namespace std;

int main()
{
    SLList<int> q;
    string line;

    cout << "\n\n\n################################################################################\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SLLIST (FIFO QUEUE) TESTS ~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "Commands:" << endl;
    cout << "  enqueue <value>              add value to the back of the queue" << endl;
    cout << "  dequeue                      remove and print value from the front" << endl;
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
            cout << q.size() << endl;
        }
        else if (cmd == "enqueue") {
            int x;
            if (!(iss >> x)) {
                cout << "Usage: enqueue <value>" << endl;
            } else {
                q.enqueue(x);
                cout << "Enqueued " << x << endl;
            }
        }
        else if (cmd == "dequeue") {
            try {
                if (q.size() == 0) {
                    cout << "Queue is empty." << endl;
                } else {
                    cout << "Dequeued: " << q.dequeue() << endl;
                }
            } catch (...) {
                cout << "Error: Queue is empty." << endl;
            }
        }
        else {
            cout << "Unknown command." << endl;
        }
        cout << "> ";
    }
    return 0;
}