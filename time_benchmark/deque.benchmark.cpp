#include <iostream>
#include <chrono>
#include "../src/arraydeque.h"

using namespace std;
using namespace std::chrono;

int main() {
    ArrayDeque<int> dq;

    const int N = 1000000;

    auto start = high_resolution_clock::now();

    // insert
    for (int i = 0; i < N; i++) {
        dq.pushBack(i);
    }

    // remove
    for (int i = 0; i < N; i++) {
        dq.popFront();
    }

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Operations: " << N * 2 << endl;
    cout << "Time: " << duration.count() << " ms" << endl;

    return 0;
}