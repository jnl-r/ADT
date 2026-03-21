#include "../src/skiplist.h"
#include <iostream>
#include <chrono>
#include <random>
#include <iomanip>
#include <vector>

using namespace std;
using namespace std::chrono;

template <typename Func>
long long measure(Func f)
{
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

void runSuite(int N)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000);

    SkipListSSet<int> set1;
    long long tAdd = measure([&]()
                             {
        for (int i = 0; i < N; ++i) {
            set1.add(dist(gen)); 
        } });

    SkipListSSet<int> set2;
    for (int i = 0; i < N; ++i)
    {
        set2.add(dist(gen));
    }
    long long tRemove = measure([&]()
                                {
        for (int i = 0; i < N; ++i) {
            set2.remove(dist(gen));
        } });

    SkipListSSet<int> set3;
    for (int i = 0; i < N; ++i)
    {
        set3.add(dist(gen));
    }
    long long tFind = measure([&]()
                              {
        for (int i = 0; i < N; ++i) {
            set3.contains(dist(gen));
        } });

    SkipListSSet<int> set4;
    mt19937 mixedGen(rd());
    uniform_int_distribution<int> mixedDist(1, 1000000);

    long long tMixed = measure([&]()
                               {
        for (int i = 0; i < N; ++i) {
            int x = mixedDist(mixedGen);
            set4.add(x);
            if (i % 3 == 0) set4.remove(x);
            set4.contains(x);
        } });

    cout << left << setw(12) << N
         << setw(15) << (to_string(tAdd) + "ms")
         << setw(15) << (to_string(tRemove) + "ms")
         << setw(15) << (to_string(tFind) + "ms")
         << setw(15) << (to_string(tMixed) + "ms") << endl;
}

int main()
{
    cout << "\nSKIP LIST (SORTED SET) PERFORMANCE (times in milliseconds)\n";
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