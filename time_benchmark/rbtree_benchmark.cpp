#include "../src/redblacktrees.h"
#include <iostream>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;
using namespace std::chrono;

template <typename Func>
long long measure(Func f) {
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

void runSuite(int N) {
    RedBlackTree<int> tree;
    
    long long tInsert = measure([&]() {
        for (int i = 0; i < N; i++) tree.add(i);
    });

    long long tSearch = measure([&]() {
        for (int i = 0; i < N; i++) tree.contains(i);
    });

    long long tRemove = measure([&]() {
        for (int i = 0; i < N; i++) tree.remove(i);
    });

    random_device rd;
    mt19937 gen(rd());
    RedBlackTree<int> mixedTree;
    long long tMixed = measure([&]() {
        for (int i = 0; i < N; i++) {
            int x = gen() % 1000000;
            mixedTree.add(x);
            if (i % 3 == 0) mixedTree.remove(x);
            mixedTree.contains(x);
        }
    });

    cout << left << setw(12) << N 
         << setw(15) << (to_string(tInsert) + "ms")
         << setw(15) << (to_string(tSearch) + "ms")
         << setw(15) << (to_string(tRemove) + "ms")
         << setw(15) << (to_string(tMixed) + "ms") << endl;
}

int main() {
    cout << "\n RED-BLACK TREE PERFORMANCE \n";
    cout << left << setw(12) << "Elements" 
         << setw(15) << "Insert" 
         << setw(15) << "Search" 
         << setw(15) << "Remove" 
         << setw(15) << "Mixed (Ops)" << endl;
    cout << string(70, '-') << endl;

    runSuite(100000);
    runSuite(500000);

    return 0;
}