#include "../src/arraystack.h"
#include <iostream>
#include <chrono>
#include <random>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;
using namespace std::chrono;

template <typename Func>
double measure(Func f) {
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

void runSuite(int N) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000);

    ArrayStack<int> st1;
    double tPush = measure([&]() {
        for (int i = 0; i < N; ++i) {
            st1.push(dist(gen));
        }
    });

    ArrayStack<int> st2;
    for (int i = 0; i < N; ++i) {
        st2.push(dist(gen));
    }
    double tPop = measure([&]() {
        for (int i = 0; i < N; ++i) {
            st2.pop();
        }
    });

    auto format = [](double t) -> string {
        ostringstream oss;
        oss << fixed << setprecision(3) << t << "ms";
        return oss.str();
    };

    cout << left << setw(12) << N
         << setw(15) << format(tPush)
         << setw(15) << format(tPop) << endl;
}

int main() {
    cout << "\nARRAYSTACK (FILO STACK) PERFORMANCE (times in milliseconds)\n";
    cout << left << setw(12) << "Elements"
         << setw(15) << "Push"
         << setw(15) << "Pop" << endl;
    cout << string(45, '-') << endl;

    vector<int> sizes = {10000, 50000, 100000, 500000, 1000000};
    for (int N : sizes) {
        runSuite(N);
    }
    cout << endl;
    return 0;
}