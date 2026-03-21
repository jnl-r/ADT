#include "../src/meldableheap.h"
#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

template <typename Func>
long long measureTime(Func f)
{
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

void benchmarkInsert(int N)
{
    MeldableHeap<int> pq;

    auto time = measureTime([&]()
    {
        for (int i = 0; i < N; i++)
            pq.push(i);
    });

    cout << "Insert (" << N << "): " << time << " ms\n";
}

void benchmarkRemoveMin(int N)
{
    MeldableHeap<int> pq;

    for (int i = 0; i < N; i++)
        pq.push(i);

    auto time = measureTime([&]()
    {
        for (int i = 0; i < N; i++)
            pq.pop();
    });

    cout << "RemoveMin (" << N << "): " << time << " ms\n";
}

void benchmarkMixed(int N)
{
    random_device rd;
    mt19937 gen(rd());

    MeldableHeap<int> pq;

    auto time = measureTime([&]()
    {
        for (int i = 0; i < N; i++)
        {
            pq.push(gen() % 1000000);
            if (i % 2 == 0) pq.pop();
        }
    });

    cout << "Mixed (" << N << "): " << time << " ms\n";
}

int main()
{
    cout << "MELDABLE HEAP BENCHMARK\n";

    int N1 = 100000;
    int N2 = 200000;

    cout << "--- SMALL ---\n";
    benchmarkInsert(N1);
    benchmarkRemoveMin(N1);
    benchmarkMixed(N1);

    cout << "\n--- LARGE ---\n";
    benchmarkInsert(N2);
    benchmarkRemoveMin(N2);
    benchmarkMixed(N2);

}