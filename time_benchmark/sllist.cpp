#include <iostream>
#include <chrono>
#include "../src/sllist.h"

using namespace std;
using namespace std::chrono;

int main() {
    int n;
    if (!(cin >> n)) return 0; 

    SLList<int> q;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        q.enqueue(i);
    }
    for (int i = 0; i < n; i++) {
        q.dequeue();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << duration.count() << endl; 
    
    return 0;
}