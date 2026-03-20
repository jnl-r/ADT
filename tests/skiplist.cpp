#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "../src/skiplist.h"

using namespace std;

template <typename T>
void printSet(const SkipListSSet<T> &set)
{
    auto vec = set.toVector();
    cout << "{";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (i > 0)
            cout << ", ";
        cout << vec[i];
    }
    cout << "}" << endl;
}

int main()
{
    SkipListSSet<int> set;
    string line;

    cout << "\n\n\n################################################################################\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SKIP LIST (SORTED SET) TESTS ~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "Commands:" << endl;
    cout << "  add <value>                  insert value (if not present)" << endl;
    cout << "  remove <value>               remove value (if present)" << endl;
    cout << "  find <value>                 check if value is in the set" << endl;
    cout << "  size                         print number of elements" << endl;
    cout << "  print                        print the set (sorted order)" << endl;
    cout << "  clear                        remove all elements" << endl;
    cout << "  quit                         exit program" << endl;
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
            printSet(set);
        }
        else if (cmd == "size")
        {
            cout << set.size() << endl;
        }
        else if (cmd == "clear")
        {
            set.clear();
            cout << "Set cleared." << endl;
        }
        else if (cmd == "add")
        {
            int x;
            if (!(iss >> x))
            {
                cout << "Usage: add <value>" << endl;
            }
            else
            {
                bool added = set.add(x);
                if (added)
                    cout << "Added " << x << endl;
                else
                    cout << x << " already exists." << endl;
                printSet(set);
            }
        }
        else if (cmd == "remove")
        {
            int x;
            if (!(iss >> x))
            {
                cout << "Usage: remove <value>" << endl;
            }
            else
            {
                bool removed = set.remove(x);
                if (removed)
                    cout << "Removed " << x << endl;
                else
                    cout << x << " not found." << endl;
                printSet(set);
            }
        }
        else if (cmd == "find")
        {
            int x;
            if (!(iss >> x))
            {
                cout << "Usage: find <value>" << endl;
            }
            else
            {
                bool found = set.contains(x);
                if (found)
                    cout << x << " is in the set." << endl;
                else
                    cout << x << " is NOT in the set." << endl;
            }
        }
        else
        {
            cout << "Unknown command." << endl;
        }

        cout << "> ";
    }

    return 0;
}