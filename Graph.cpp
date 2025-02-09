/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/


#include "Graph.h"
#include <iostream>
using namespace std;

/**
 * Constructor
 * Process: Initializes an empty graph using an adjacency list.
 * Precondition: None.
 * Postcondition: A new `Graph` object is created with an empty adjacency list.
 */
Graph::Graph() {}


/**
 * Destructor
 * Process: Calls `clearGraph()` to free dynamically allocated memory.
 * Precondition: None.
 * Postcondition: All memory allocated for the graph is released.
 */
Graph::~Graph() {
    clearGraph();
}


/**
 * Adds a new node to the graph.
 * Process: Checks if the node already exists in the adjacency list. If not, inserts a new entry.
 * Precondition: `node` must be a valid non-empty string.
 * Postcondition: A new node is added to the graph unless it already exists.
 */
void Graph::addNode(const string& node) {
    if (!adjacencyList.contains(node)) {
        adjacencyList.insert(node, new List<string>());
    }
}


/**
 * Adds an edge (connection) between two nodes.
 * Process: Ensures both nodes exist in the graph, then adds each node to the other's adjacency list.
 * Precondition: `node1` and `node2` must be valid non-empty strings.
 * Postcondition: A bidirectional edge is created between `node1` and `node2`.
 */
void Graph::addEdge(const string& node1, const string& node2) {
    addNode(node1);
    addNode(node2);

    adjacencyList.get(node1)->add(node2);
    adjacencyList.get(node2)->add(node1);
}


/**
 * Retrieves the list of connected nodes (neighbors) for a given node.
 * Process: Checks if the node exists in the adjacency list. If found, returns a pointer to its connections.
 * Precondition: `node` must be a valid string.
 * Postcondition: Returns a pointer to a `List<string>` of connected nodes, or `nullptr` if the node is not found.
 */
List<string>* Graph::getConnections(const string& node) const {
    if (adjacencyList.contains(node)) {
        return adjacencyList.get(node);
    }
    return nullptr;
}


/**
 * Displays the graph's adjacency list.
 * Process: Iterates through the adjacency list and prints each node and its connections.
 * Precondition: The graph must be populated with at least one node.
 * Postcondition: The entire graph structure is displayed in the console.
 */
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


/**
 * Clears all nodes and edges from the graph.
 * Process: Iterates through the adjacency list, deletes dynamically allocated lists, and clears the adjacency list.
 * Precondition: None.
 * Postcondition: The graph is emptied, with all memory freed.
 */
void Graph::clearGraph() {
    auto it = adjacencyList.createIterator();
    while (it->hasNext()) {
        delete it->next()->value;
    }
    delete it;
    adjacencyList.clear();
}


/**
 * Checks if a given node represents an actor.
 * Process: Looks up the node in the adjacency list and verifies if it has the "Actor:" prefix.
 * Precondition: `node` must be a valid string.
 * Postcondition: Returns `true` if the node represents an actor; otherwise, returns `false`.
 */
bool Graph::isActor(const string& node) const {
    return adjacencyList.contains(node) && node.find("Actor:") == 0; // Adjust based on your data format
}


/**
 * Finds the most influential actor in the graph.
 * Process: Iterates through all nodes, checking for actors, and selects the actor with the highest degree centrality (most connections).
 * Precondition: The graph must contain actors and their movie associations.
 * Postcondition: Returns the name of the most influential actor based on connections. The "Actor:" prefix is removed before returning.
 */
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

    // Remove "Actor:" prefix from result before returning
    if (!mostInfluentialActor.empty()) {
        return mostInfluentialActor.substr(6);
    }
    return mostInfluentialActor;
}

