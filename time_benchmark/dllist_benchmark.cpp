#include "../src/dllist.h"
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
    uniform_int_distribution<int> valDist(1, 1000000);

    DLList<int> list1;
    long long tPushFront = measure([&]()
                                   {
        for (int i = 0; i < N; ++i) list1.add(0, i); });

    DLList<int> list2;
    long long tPushBack = measure([&]()
                                  {
        for (int i = 0; i < N; ++i)
        {
            list2.add(list2.size(), i);
        } });

    DLList<int> list3;
    for (int i = 0; i < N / 10; ++i)
    {
        list3.add(list3.size(), i);
    }
    long long tInsert = measure([&]()
                                {
        for (int i = 0; i < N; ++i) {
            uniform_int_distribution<size_t> posDist(0, list3.size());
            list3.add(posDist(gen), valDist(gen));
        } });

    DLList<int> list4;
    for (int i = 0; i < N * 2; ++i)
    {
        list4.add(list4.size(), i);
    }
    long long tRemove = measure([&]()
                                {
        for (int i = 0; i < N; ++i) {
            uniform_int_distribution<size_t> posDist(0, list4.size() - 1);
            list4.remove(posDist(gen));
        } });

    DLList<int> list5;
    for (int i = 0; i < N * 2; ++i)
    {
        list5.add(list5.size(), i);
    }
    uniform_int_distribution<size_t> posDist(0, list5.size() - 1);
    long long tGetSet = measure([&]()
                                {
        for (int i = 0; i < N; ++i) {
            size_t pos = posDist(gen);
            int val = list5.get(pos);
            list5.set(pos, val + 1);
        } });

    cout << left << setw(12) << N
         << setw(15) << (to_string(tPushFront) + "ms")
         << setw(15) << (to_string(tPushBack) + "ms")
         << setw(15) << (to_string(tInsert) + "ms")
         << setw(15) << (to_string(tRemove) + "ms")
         << setw(15) << (to_string(tGetSet) + "ms") << endl;
}

int main()
{
    cout << "\nDOUBLY LINKED LIST PERFORMANCE (times in milliseconds)\n";
    cout << left << setw(12) << "Elements"
         << setw(15) << "Push Front"
         << setw(15) << "Push Back"
         << setw(15) << "Insert"
         << setw(15) << "Remove"
         << setw(15) << "Get/Set" << endl;
    cout << string(85, '-') << endl;

    vector<int> sizes = {10000, 50000, 100000, 500000, 1000000};
    for (int N : sizes)
    {
        runSuite(N);
    }

    return 0;
}