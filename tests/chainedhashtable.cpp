#include <iostream>
#include "../src/chainedhashtable.h"

using namespace std;

int main() {
    ChainedHashTable<int> set;
    
    cout << "UNSORTED SET TESTS" << endl;
    
    set.add(10);
    set.add(20);
    set.add(30);
    cout << "Added 10, 20, 30. Size: " << set.size() << " (Expected 3)" << endl;
    
    bool addedDuplicate = set.add(20);
    cout << "Tried adding 20 again. Success? " << (addedDuplicate ? "Yes" : "No") << " (Expected No)" << endl;
    cout << "Size is still: " << set.size() << " (Expected 3)" << endl;
    
    cout << "Contains 10? " << (set.find(10) ? "Yes" : "No") << " (Expected Yes)" << endl;
    cout << "Contains 99? " << (set.find(99) ? "Yes" : "No") << " (Expected No)" << endl;
    
    set.remove(10);
    cout << "Removed 10. Contains 10? " << (set.find(10) ? "Yes" : "No") << " (Expected No)" << endl;
    cout << "Final size: " << set.size() << " (Expected 2)" << endl;
    
    return 0;
}