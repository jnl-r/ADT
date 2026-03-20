#include <iostream>
#include <chrono>
#include "../src/chainedhashtable.h"

using namespace std;
using namespace std::chrono;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    ChainedHashTable<int> set;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        set.add(i);
    }
    for (int i = 0; i < n; i++) {
        set.find(i);
    }
    for (int i = 0; i < n; i++) {
        set.remove(i);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << duration.count() << endl;
    
    return 0;
}