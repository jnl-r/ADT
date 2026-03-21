#pragma once
#include <vector>
#include "../include/graph.h"

using namespace std;

class AdjacencyMatrix : public Graph<bool>
{
private:
    int n;
    vector<vector<bool>> a;

public:
    AdjacencyMatrix(int vertices) : n(vertices),
                                    a(vertices,
                                      vector<bool>(vertices, false)) {}

    void addEdge(int i, int j) override
    {
        a[i][j] = true;
    }

    void removeEdge(int i, int j) override
    {
        a[i][j] = false;
    }

    bool hasEdge(int i, int j) const override
    {
        return a[i][j];
    }

    vector<int> outEdges(int i) const override
    {
        vector<int> edges;
        for (int j = 0; j < n; ++j)
        {
            if (a[i][j])
                edges.push_back(j);
        }
        return edges;
    }

    vector<int> inEdges(int i) const override
    {
        vector<int> edges;
        for (int j = 0; j < n; ++j)
        {
            if (a[j][i])
                edges.push_back(j);
        }
        return edges;
    }

    int nVertices() const override
    {
        return n;
    }
};