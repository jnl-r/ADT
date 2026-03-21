#include "../src/arraydeque.h"
#include <iostream>
#include <chrono>
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

string formatMs(double time) {
    stringstream ss;
    ss << fixed << setprecision(3) << time << "ms";
    return ss.str();
}

void runSuite(int N) {
    ArrayDeque<int> dq;
    
    //PushFront
    double tPushFront = measure([&]() {
        for (int i = 0; i < N; i++) dq.pushFront(i);
    });

    //PushBack
    ArrayDeque<int> dq2; // Fresh deque for Back tests
    double tPushBack = measure([&]() {
        for (int i = 0; i < N; i++) dq2.pushBack(i);
    });

    //Pop Tests (removing from the back of dq2)
    double tPop = measure([&]() {
        for (int i = 0; i < N; i++) dq2.popBack();
    });

    //Mixed (Push back, Pop front)
    ArrayDeque<int> dq3;
    double tMixed = measure([&]() {
        for (int i = 0; i < N; i++) {
            dq3.pushBack(i);
            if (i % 2 == 0) dq3.popFront();
        }
    });

    cout << left << setw(12) << N 
         << setw(18) << formatMs(tPushFront)
         << setw(18) << formatMs(tPushBack)
         << setw(18) << formatMs(tPop)
         << setw(18) << formatMs(tMixed) << endl;
}

int main() {
    cout << "\n ARRAY DEQUE PERFORMANCE \n";
    cout << left << setw(12) << "Elements" 
         << setw(18) << "PushFront" 
         << setw(18) << "PushBack" 
         << setw(18) << "PopBack" 
         << setw(18) << "Mixed (Ops)" << endl;
    cout << string(80, '-') << endl;

    runSuite(10000);
    runSuite(50000);
    runSuite(100000);
    runSuite(500000);
    runSuite(1000000);

    return 0;
}