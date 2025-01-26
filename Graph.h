#pragma once
#pragma once
#include "Map.h"
#include "List.h"
#include <string>

using namespace std;

class Graph
{
private:
    Map<string, List<string>*> adjacencyList; // Adjacency list mapping node (actor/movie) to connected nodes

public:
    Graph();
    ~Graph();

    void addNode(const string& node);
    void addEdge(const string& node1, const string& node2);
    List<string>* getConnections(const string& node) const;
    void displayGraph() const;
    void clearGraph();
};

