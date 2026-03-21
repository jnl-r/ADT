#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "../src/chainedhashtable.h"

using namespace std;

int main()
{
    ChainedHashTable<int> set;
    string line;

    cout << "\n\n\n################################################################################\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~ CHAINED HASH TABLE (UNSORTED SET) TESTS ~~~~~~~~~~~~~~~~~~\n";
    cout << "Commands:" << endl;
    cout << "  add <value>                  insert value (if not present)" << endl;
    cout << "  remove <value>               remove value (if present)" << endl;
    cout << "  find <value>                 check if value is in the set" << endl;
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
            cout << set.size() << endl;
        }
        else if (cmd == "add") {
            int x;
            if (!(iss >> x)) {
                cout << "Usage: add <value>" << endl;
            } else {
                bool added = set.add(x);
                if (added) cout << "Added " << x << endl;
                else cout << x << " already exists." << endl;
            }
        }
        else if (cmd == "remove") {
            int x;
            if (!(iss >> x)) {
                cout << "Usage: remove <value>" << endl;
            } else {
                bool removed = set.remove(x);
                if (removed) cout << "Removed " << x << endl;
                else cout << x << " not found." << endl;
            }
        }
        else if (cmd == "find") {
            int x;
            if (!(iss >> x)) {
                cout << "Usage: find <value>" << endl;
            } else {
                bool found = set.find(x);
                if (found) cout << x << " is in the set." << endl;
                else cout << x << " is NOT in the set." << endl;
            }
        }
        else {
            cout << "Unknown command." << endl;
        }
        cout << "> ";
    }
    return 0;
}