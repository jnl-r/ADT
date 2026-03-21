#include "../src/adjacencymatrix.h"
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
    AdjacencyMatrix graph(N);

    double tAdd = measure([&]()
                          {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i != j) graph.addEdge(i, j);
            }
        } });

    double tRemove = measure([&]()
                             {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i != j) graph.removeEdge(i, j);
            }
        } });

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (i != j)
                graph.addEdge(i, j);

    double tHas = measure([&]()
                          {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                graph.hasEdge(i, j);
            }
        } });

    double tOut = measure([&]()
                          {
        for (int i = 0; i < N; ++i) {
            graph.outEdges(i);
        } });

    double tIn = measure([&]()
                         {
        for (int i = 0; i < N; ++i) {
            graph.inEdges(i);
        } });

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> vertDist(0, N - 1);
    uniform_int_distribution<int> opDist(0, 2);
    const long long MIXED_OPS = 100000;

    AdjacencyMatrix mixedGraph(N);
    double tMixed = measure([&]()
                            {
        for (long long k = 0; k < MIXED_OPS; ++k) {
            int i = vertDist(gen);
            int j = vertDist(gen);
            if (i == j) continue;
            int op = opDist(gen);
            if (op == 0) mixedGraph.addEdge(i, j);
            else if (op == 1) mixedGraph.removeEdge(i, j);
            else mixedGraph.hasEdge(i, j);
        } });

    auto format = [](double t) -> string
    {
        ostringstream oss;
        oss << fixed << setprecision(3) << t << "ms";
        return oss.str();
    };

    cout << left << setw(12) << N
         << setw(15) << format(tAdd)
         << setw(15) << format(tRemove)
         << setw(15) << format(tHas)
         << setw(15) << format(tOut)
         << setw(15) << format(tIn)
         << setw(15) << format(tMixed) << endl;
}

int main()
{
    cout << "\nADJACENCY MATRIX GRAPH PERFORMANCE (times in milliseconds)\n";
    cout << left << setw(12) << "Vertices"
         << setw(15) << "Add All"
         << setw(15) << "Remove All"
         << setw(15) << "Has All"
         << setw(15) << "Out Edges"
         << setw(15) << "In Edges"
         << setw(15) << "Mixed (2M ops)" << endl;
    cout << string(100, '-') << endl;

    vector<int> sizes = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    for (int N : sizes)
    {
        runSuite(N);
    }

    return 0;
}