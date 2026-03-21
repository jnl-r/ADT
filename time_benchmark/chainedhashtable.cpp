#include "../src/chainedhashtable.h"
#include <iostream>
#include <chrono>
#include <random>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;
using namespace std::chrono;

template <typename Func>
double measure(Func f)
{
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

void runSuite(int N)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000);

    ChainedHashTable<int> set1;
    double tAdd = measure([&]() {
        for (int i = 0; i < N; ++i) {
            set1.add(dist(gen));
        } 
    });

    ChainedHashTable<int> set2;
    for (int i = 0; i < N; ++i) {
        set2.add(dist(gen));
    }
    double tRemove = measure([&]() {
        for (int i = 0; i < N; ++i) {
            set2.remove(dist(gen));
        } 
    });

    ChainedHashTable<int> set3;
    for (int i = 0; i < N; ++i) {
        set3.add(dist(gen));
    }
    double tFind = measure([&]() {
        for (int i = 0; i < N; ++i) {
            set3.find(dist(gen));
        } 
    });

    ChainedHashTable<int> set4;
    mt19937 mixedGen(rd());
    uniform_int_distribution<int> mixedDist(1, 1000000);

    double tMixed = measure([&]() {
        for (int i = 0; i < N; ++i) {
            int x = mixedDist(mixedGen);
            set4.add(x);
            if (i % 3 == 0) set4.remove(x);
            set4.find(x);
        } 
    });

    auto format = [](double t) -> string {
        ostringstream oss;
        oss << fixed << setprecision(3) << t << "ms";
        return oss.str();
    };

    cout << left << setw(12) << N
         << setw(15) << format(tAdd)
         << setw(15) << format(tRemove)
         << setw(15) << format(tFind)
         << setw(15) << format(tMixed) << endl;
}

int main()
{
    cout << "\nCHAINED HASH TABLE (UNSORTED SET) PERFORMANCE (times in milliseconds)\n";
    cout << left << setw(12) << "Elements"
         << setw(15) << "Add"
         << setw(15) << "Remove"
         << setw(15) << "Find"
         << setw(15) << "Mixed" << endl;
    cout << string(70, '-') << endl;

    vector<int> sizes = {10000, 50000, 100000, 500000, 1000000};
    for (int N : sizes)
    {
        runSuite(N);
    }

    cout << endl;
    return 0;
}