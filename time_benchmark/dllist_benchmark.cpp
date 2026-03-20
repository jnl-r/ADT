#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include <sstream>
#include "../src/dllist.h"

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
    DLList<int> list;
    auto time = measureTime([&]()
                            {
        for (int i = 0; i < N; ++i) {
            list.add(0, i);
        } });
    cout << "Push front (" << N << " operations): " << time << " ms\n";
}

void benchmarkPushBack(int N)
{
    DLList<int> list;
    auto time = measureTime([&]()
                            {
        for (int i = 0; i < N; ++i) {
            list.add(list.size(), i);
        } });
    cout << "Push back (" << N << " operations): " << time << " ms\n";
}

void benchmarkRandomInserts(int N)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> valDist(1, 1000000);

    DLList<int> list;
    // filling initial data
    for (int i = 0; i < N / 10; ++i)
        list.add(list.size(), i);

    auto time = measureTime([&]()
                            {
        for (int i = 0; i < N; ++i) {
            // random position within the current list size
            uniform_int_distribution<size_t> posDist(0, list.size());
            size_t pos = posDist(gen);
            list.add(pos, valDist(gen));
        } });
    cout << "Random inserts (" << N << " operations): " << time << " ms\n";
}

void benchmarkRandomRemoves(int N)
{
    random_device rd;
    mt19937 gen(rd());

    DLList<int> list;
    for (int i = 0; i < N * 2; ++i)
        list.add(list.size(), i);

    auto time = measureTime([&]()
                            {
        for (int i = 0; i < N; ++i) {
            // random index within the current list size
            uniform_int_distribution<size_t> posDist(0, list.size() - 1);
            size_t pos = posDist(gen);
            list.remove(pos);
        } });
    cout << "Random removes (" << N << " operations): " << time << " ms\n";
}

void benchmarkRandomGetSet(int N)
{
    random_device rd;
    mt19937 gen(rd());

    DLList<int> list;
    for (int i = 0; i < N * 2; ++i)
        list.add(list.size(), i);

    uniform_int_distribution<size_t> posDist(0, list.size() - 1);

    auto time = measureTime([&]()
                            {
        for (int i = 0; i < N; ++i) {
            size_t pos = posDist(gen);
            int val = list.get(pos);
            list.set(pos, val + 1);
        } });
    cout << "Random get/set (" << N << " operations): " << time << " ms\n";
}

int main()
{
    string line;
    cout << "\n\n\n################################################################################\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DLLIST TIME BENCHMARK" << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "\nCommands:" << endl;
    cout << "  all <N>                     run all benchmarks with N operations" << endl;
    cout << "  pushfront <N>               push front N times" << endl;
    cout << "  pushback <N>                push back N times" << endl;
    cout << "  randominserts <N>           random inserts N times" << endl;
    cout << "  randomremoves <N>           random removes N times" << endl;
    cout << "  randomgetset <N>            random get/set N times" << endl;
    cout << "  quit                        exit" << endl;
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
                benchmarkPushFront(N);
                benchmarkPushBack(N);
                benchmarkRandomInserts(N);
                benchmarkRandomRemoves(N);
                benchmarkRandomGetSet(N);
                cout << "--------------------------------------------------------------------------------\n";
                cout << "################################################################################\n";
            }
        }
        else if (cmd == "pushfront")
        {
            int N;
            if (!(iss >> N) || N <= 0)
            {
                cout << "Please provide a positive integer N." << endl;
            }
            else
            {
                benchmarkPushFront(N);
            }
        }
        else if (cmd == "pushback")
        {
            int N;
            if (!(iss >> N) || N <= 0)
            {
                cout << "Please provide a positive integer N." << endl;
            }
            else
            {
                benchmarkPushBack(N);
            }
        }
        else if (cmd == "randominserts")
        {
            int N;
            if (!(iss >> N) || N <= 0)
            {
                cout << "Please provide a positive integer N." << endl;
            }
            else
            {
                benchmarkRandomInserts(N);
            }
        }
        else if (cmd == "randomremoves")
        {
            int N;
            if (!(iss >> N) || N <= 0)
            {
                cout << "Please provide a positive integer N." << endl;
            }
            else
            {
                benchmarkRandomRemoves(N);
            }
        }
        else if (cmd == "randomgetset")
        {
            int N;
            if (!(iss >> N) || N <= 0)
            {
                cout << "Please provide a positive integer N." << endl;
            }
            else
            {
                benchmarkRandomGetSet(N);
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