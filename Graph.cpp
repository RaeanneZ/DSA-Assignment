#include "Graph.h"
#include <iostream>
using namespace std;

Graph::Graph() {}

Graph::~Graph() {
    clearGraph();
}

void Graph::addNode(const string& node) {
    if (!adjacencyList.contains(node)) {
        adjacencyList.insert(node, new List<string>());
    }
}

void Graph::addEdge(const string& node1, const string& node2) {
    addNode(node1);
    addNode(node2);

    adjacencyList.get(node1)->add(node2);
    adjacencyList.get(node2)->add(node1);
}

List<string>* Graph::getConnections(const string& node) const {
    if (adjacencyList.contains(node)) {
        return adjacencyList.get(node);
    }
    return nullptr;
}

void Graph::displayGraph() const {
    auto it = adjacencyList.createIterator();
    while (it->hasNext()) {
        auto pair = it->next();
        cout << pair->key << ": ";
        auto connections = pair->value->createIterator();
        while (connections->hasNext()) {
            cout << connections->next() << ", ";
        }
        delete connections;
        cout << endl;
    }
    delete it;
}

void Graph::clearGraph() {
    auto it = adjacencyList.createIterator();
    while (it->hasNext()) {
        delete it->next()->value;
    }
    delete it;
    adjacencyList.clear();
}

// **Find Most Influential Actor**
bool Graph::isActor(const string& node) const {
    return adjacencyList.contains(node) && node.find("Actor:") == 0; // Adjust based on your data format
}

string Graph::findMostInfluentialActor() {
    string mostInfluentialActor;
    int maxConnections = -1;

    auto it = adjacencyList.createIterator();
    while (it->hasNext()) {
        auto pair = it->next();
        string node = pair->key;

        // Skip non-actor nodes
        if (!isActor(node)) {
            continue;
        }

        // Calculate degree centrality
        int connections = pair->value->getSize();
        if (connections > maxConnections) {
            maxConnections = connections;
            mostInfluentialActor = node;
        }
    }
    delete it;

    return mostInfluentialActor;
}

