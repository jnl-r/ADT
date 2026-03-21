#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "../src/adjacencymatrix.h"

using namespace std;

void printEdges(const vector<int> &edges)
{
    cout << "[";
    for (size_t i = 0; i < edges.size(); ++i)
    {
        if (i > 0)
            cout << ", ";
        cout << edges[i];
    }
    cout << "]";
}

int main()
{
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;
    AdjacencyMatrix graph(n);
    string line;
    getline(cin, line);

    cout << "\n\n\n################################################################################\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ADJACENCY MATRIX GRAPH TESTS ~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "Commands:\n";
    cout << "  add <i> <j>                     add edge i->j\n";
    cout << "  remove <i> <j>                  remove edge i->j\n";
    cout << "  has <i> <j>                     check if edge i->j exists\n";
    cout << "  out <i>                         list outgoing edges from i\n";
    cout << "  in <i>                          list incoming edges to i\n";
    cout << "  size                            number of vertices\n";
    cout << "  quit                            exit\n";
    cout << "--------------------------------------------------------------------------------\n";
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
        else if (cmd == "size")
        {
            cout << graph.nVertices() << endl;
        }
        else if (cmd == "add")
        {
            int i, j;
            if (!(iss >> i >> j))
            {
                cout << "Usage: add <i> <j>" << endl;
            }
            else if (i < 0 || i >= n || j < 0 || j >= n)
            {
                cout << "Vertex index out of range." << endl;
            }
            else
            {
                graph.addEdge(i, j);
                cout << "Added edge " << i << " -> " << j << endl;
            }
        }
        else if (cmd == "remove")
        {
            int i, j;
            if (!(iss >> i >> j))
            {
                cout << "Usage: remove <i> <j>" << endl;
            }
            else if (i < 0 || i >= n || j < 0 || j >= n)
            {
                cout << "Vertex index out of range." << endl;
            }
            else
            {
                graph.removeEdge(i, j);
                cout << "Removed edge " << i << " -> " << j << endl;
            }
        }
        else if (cmd == "has")
        {
            int i, j;
            if (!(iss >> i >> j))
            {
                cout << "Usage: has <i> <j>" << endl;
            }
            else if (i < 0 || i >= n || j < 0 || j >= n)
            {
                cout << "Vertex index out of range." << endl;
            }
            else
            {
                bool exists = graph.hasEdge(i, j);
                cout << (exists ? "Exists" : "Does not exist") << endl;
            }
        }
        else if (cmd == "out")
        {
            int i;
            if (!(iss >> i))
            {
                cout << "Usage: out <i>" << endl;
            }
            else if (i < 0 || i >= n)
            {
                cout << "Vertex index out of range." << endl;
            }
            else
            {
                vector<int> edges = graph.outEdges(i);
                cout << "Outgoing edges from " << i << ": ";
                printEdges(edges);
                cout << endl;
            }
        }
        else if (cmd == "in")
        {
            int i;
            if (!(iss >> i))
            {
                cout << "Usage: in <i>" << endl;
            }
            else if (i < 0 || i >= n)
            {
                cout << "Vertex index out of range." << endl;
            }
            else
            {
                vector<int> edges = graph.inEdges(i);
                cout << "Incoming edges to " << i << ": ";
                printEdges(edges);
                cout << endl;
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