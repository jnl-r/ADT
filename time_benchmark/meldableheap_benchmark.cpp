#include "../src/meldableheap.h"
#include <iostream>
#include <chrono>
#include <random>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;
using namespace std::chrono;

template <typename Func>
double measure(Func f) {
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    
    auto us = duration_cast<microseconds>(end - start).count();
    return static_cast<double>(us) / 1000.0; 
}

// Helper to format the output string "X.XXXms"
string formatMs(double time) {
    stringstream ss;
    ss << fixed << setprecision(3) << time << "ms";
    return ss.str();
}

void runSuite(int N) {
    MeldableHeap<int> heap;
    
    double tInsert = measure([&]() {
        for (int i = 0; i < N; i++) heap.push(i); 
    });

    double tRemove = measure([&]() {
        for (int i = 0; i < N; i++) heap.pop(); 
    });

    //Mixed (Randomized Add/Remove)
    random_device rd;
    mt19937 gen(rd());
    MeldableHeap<int> mixedHeap;
    double tMixed = measure([&]() {
        for (int i = 0; i < N; i++) {
            mixedHeap.push(gen() % 1000000);
            if (i % 2 == 0) mixedHeap.pop();
        }
    });

    cout << left << setw(12) << N 
         << setw(18) << formatMs(tInsert)
         << setw(18) << formatMs(tRemove)
         << setw(18) << formatMs(tMixed) << endl;
}

int main() {
    cout << "\n MELDABLE HEAP PERFORMANCE \n";
    cout << left << setw(12) << "Elements" 
         << setw(18) << "Insert (Add)" 
         << setw(18) << "Remove (Min)" 
         << setw(18) << "Mixed (Ops)" << endl;
    cout << string(66, '-') << endl;

    runSuite(10000);
    runSuite(50000);
    runSuite(100000);
    runSuite(500000);
    runSuite(1000000);

    return 0;
}