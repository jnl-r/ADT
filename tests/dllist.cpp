#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "../src/dllist.h"

using namespace std;

template <typename T>
void printList(const DLList<T> &list)
{
    cout << "[";
    for (size_t i = 0; i < list.size(); ++i)
    {
        if (i > 0)
            cout << ", ";
        cout << list.get(i);
    }
    cout << "]" << endl;
}

int main()
{
    DLList<int> list;
    string line;

    cout << "\n\n\n################################################################################\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~ DOUBLY LINKED LIST TESTS" << " ~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "Commands:" << endl;
    cout << "  add <index> <value>              insert value at index" << endl;
    cout << "  remove <index>                   remove and return element at index" << endl;
    cout << "  get <index>                      return element at index" << endl;
    cout << "  set <index> <value>              replace element at index, return old" << endl;
    cout << "  size                             print number of elements" << endl;
    cout << "  print                            print the list" << endl;
    cout << "  quit                             exit program" << endl;
    cout << "--------------------------------------------------------------------------------\n";
    cout << "################################################################################\n";

    cout << "> ";
    while (getline(cin, line))
    {
        if (line.empty())
        {
            cout << "> ";
            continue;
        }

        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "quit" || cmd == "exit")
        {
            break;
        }
        else if (cmd == "print")
        {
            printList(list);
        }
        else if (cmd == "size")
        {
            cout << list.size() << endl;
        }
        else if (cmd == "add")
        {
            size_t i;
            int x;
            if (!(iss >> i >> x))
            {
                cout << "Usage: add <index> <value>" << endl;
            }
            else
            {
                try
                {
                    list.add(i, x);
                    printList(list);
                }
                catch (const out_of_range &e)
                {
                    cout << "Error: " << e.what() << endl;
                }
            }
        }
        else if (cmd == "remove")
        {
            size_t i;
            if (!(iss >> i))
            {
                cout << "Usage: remove <index>" << endl;
            }
            else
            {
                try
                {
                    int val = list.remove(i);
                    cout << "Removed: " << val << endl;
                    printList(list);
                }
                catch (const out_of_range &e)
                {
                    cout << "Error: " << e.what() << endl;
                }
            }
        }
        else if (cmd == "get")
        {
            size_t i;
            if (!(iss >> i))
            {
                cout << "Usage: get <index>" << endl;
            }
            else
            {
                try
                {
                    int val = list.get(i);
                    cout << "Value: " << val << endl;
                }
                catch (const out_of_range &e)
                {
                    cout << "Error: " << e.what() << endl;
                }
            }
        }
        else if (cmd == "set")
        {
            size_t i;
            int x;
            if (!(iss >> i >> x))
            {
                cout << "Usage: set <index> <value>" << endl;
            }
            else
            {
                try
                {
                    int old = list.set(i, x);
                    cout << "Old value: " << old << endl;
                    printList(list);
                }
                catch (const out_of_range &e)
                {
                    cout << "Error: " << e.what() << endl;
                }
            }
        }
        else
        {
            cout << "Unknown command" << endl;
        }

        cout << "> ";
    }

    return 0;
}