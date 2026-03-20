#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include <sstream>
#include "../src/skiplist.h"

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

void benchmarkAdd(int N)
{
    SkipListSSet<int> set;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000);

    auto time = measureTime([&]()
                            {
        for (int i = 0; i < N; ++i) {
            set.add(dist(gen));
        } });
    cout << "Add (" << N << " operations): " << time << " ms\n";
}

void benchmarkRemove(int N)
{
    SkipListSSet<int> set;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000);

    for (int i = 0; i < N; ++i)
    {
        set.add(dist(gen));
    }

    auto time = measureTime([&]()
                            {
        for (int i = 0; i < N; ++i) {
            set.remove(dist(gen));
        } });
    cout << "Remove (" << N << " operations): " << time << " ms\n";
}

void benchmarkFind(int N)
{
    SkipListSSet<int> set;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000);

    for (int i = 0; i < N; ++i)
    {
        set.add(dist(gen));
    }

    auto time = measureTime([&]()
                            {
        for (int i = 0; i < N; ++i) {
            set.contains(dist(gen));
        } });
    cout << "Find (" << N << " operations): " << time << " ms\n";
}

int main()
{
    string line;
    cout << "\n\n\n################################################################################\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~ SKIP LIST (SORTED SET) BENCHMARK ~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "\nCommands:" << endl;
    cout << "  all <N>                      run all benchmarks with N operations" << endl;
    cout << "  add <N>                       test insert N times" << endl;
    cout << "  remove <N>                    test remove N times" << endl;
    cout << "  find <N>                      test find N times" << endl;
    cout << "  quit                          exit" << endl;
    cout << "\n--------------------------------------------------------------------------------\n";
    cout << "################################################################################\n";

    cout << "> ";
    while (getline(cin, line))
    {
        if (line.empty())
        {
            cout << "> ";
            continue;
        }

        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "quit" || cmd == "exit")
        {
            break;
        }
        else if (cmd == "all")
        {
            int N;
            if (!(iss >> N) || N <= 0)
            {
                cout << "Please provide a positive integer N." << endl;
            }
            else
            {
                cout << "\n\n\n################################################################################\n";
                cout << "~~~~~~~~~~~~~~~~~~~~ RUNNING ALL BENCHMARKS WITH N = " << N << " ~~~~~~~~~~~~~~~~~~~\n";
                cout << "(note: some may take longer, especially if N is large. So, just wait...) " << "\n\n";
                benchmarkAdd(N);
                benchmarkRemove(N);
                benchmarkFind(N);
                cout << "--------------------------------------------------------------------------------\n";
                cout << "################################################################################\n";
            }
        }
        else if (cmd == "add")
        {
            int N;
            if (!(iss >> N) || N <= 0)
            {
                cout << "Please provide a positive integer N." << endl;
            }
            else
            {
                benchmarkAdd(N);
            }
        }
        else if (cmd == "remove")
        {
            int N;
            if (!(iss >> N) || N <= 0)
            {
                cout << "Please provide a positive integer N." << endl;
            }
            else
            {
                benchmarkRemove(N);
            }
        }
        else if (cmd == "find")
        {
            int N;
            if (!(iss >> N) || N <= 0)
            {
                cout << "Please provide a positive integer N." << endl;
            }
            else
            {
                benchmarkFind(N);
            }
        }
        else
        {
            cout << "Unknown command." << endl;
        }

        cout << "> ";
    }

    return 0;
}