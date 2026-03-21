#include "../src/arraydeque.h"
#include <iostream>
#include <chrono>

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

void benchmarkPushFront(int N)
{
    ArrayDeque<int> dq;

    auto time = measureTime([&]()
    {
        for (int i = 0; i < N; i++)
            dq.pushFront(i);
    });

    cout << "PushFront (" << N << "): " << time << " ms\n";
}

void benchmarkPushBack(int N)
{
    ArrayDeque<int> dq;

    auto time = measureTime([&]()
    {
        for (int i = 0; i < N; i++)
            dq.pushBack(i);
    });

    cout << "PushBack (" << N << "): " << time << " ms\n";
}

void benchmarkMixed(int N)
{
    ArrayDeque<int> dq;

    auto time = measureTime([&]()
    {
        for (int i = 0; i < N; i++)
        {
            dq.pushBack(i);
            if (i % 2 == 0) dq.popFront();
        }
    });

    cout << "Mixed (" << N << "): " << time << " ms\n";
}

int main()
{
    cout << "ARRAY DEQUE BENCHMARK\n";

    int N1 = 100000;
    int N2 = 200000;

    cout << "--- SMALL ---\n";
    benchmarkPushFront(N1);
    benchmarkPushBack(N1);
    benchmarkMixed(N1);

    cout << "\n--- LARGE ---\n";
    benchmarkPushFront(N2);
    benchmarkPushBack(N2);
    benchmarkMixed(N2);

}