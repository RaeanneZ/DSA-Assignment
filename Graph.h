/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/


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

    bool isActor(const string& node) const;
    string findMostInfluentialActor(); // New function
};

