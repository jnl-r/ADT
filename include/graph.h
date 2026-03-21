#pragma once
#include <vector>
#include <cstddef>

template <typename T>
class Graph
{
public:
    virtual ~Graph() = default;
    virtual void addEdge(int i, int j) = 0;
    virtual void removeEdge(int i, int j) = 0;
    virtual bool hasEdge(int i, int j) const = 0;
    virtual std::vector<int> outEdges(int i) const = 0;
    virtual std::vector<int> inEdges(int i) const = 0;
    virtual int nVertices() const = 0;
};