#include "../src/redblacktrees.h"
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
    
    // Use microseconds for high precision
    auto us = duration_cast<microseconds>(end - start).count();
    return static_cast<double>(us) / 1000.0; 
}

string formatMs(double time) {
    stringstream ss;
    ss << fixed << setprecision(3) << time << "ms";
    return ss.str();
}

void runSuite(int N) {
    RedBlackTree<int> tree;
    
    double tInsert = measure([&]() {
        for (int i = 0; i < N; i++) tree.add(i);
    });

    double tSearch = measure([&]() {
        for (int i = 0; i < N; i++) tree.contains(i);
    });

    double tRemove = measure([&]() {
        for (int i = 0; i < N; i++) tree.remove(i);
    });

    random_device rd;
    mt19937 gen(rd());
    RedBlackTree<int> mixedTree;
    double tMixed = measure([&]() {
        for (int i = 0; i < N; i++) {
            int x = gen() % 1000000;
            mixedTree.add(x);
            if (i % 3 == 0) mixedTree.remove(x);
            mixedTree.contains(x);
        }
    });

    cout << left << setw(12) << N 
         << setw(18) << formatMs(tInsert)
         << setw(18) << formatMs(tSearch)
         << setw(18) << formatMs(tRemove)
         << setw(18) << formatMs(tMixed) << endl;
}

int main() {
    cout << "\nRED-BLACK TREE PERFORMANCE \n";
    cout << left << setw(12) << "Elements" 
         << setw(18) << "Insert" 
         << setw(18) << "Search" 
         << setw(18) << "Remove" 
         << setw(18) << "Mixed (Ops)" << endl;
    cout << string(80, '-') << endl;

    runSuite(10000);
    runSuite(50000);
    runSuite(100000);
    runSuite(500000);
    runSuite(1000000);

    return 0;
}