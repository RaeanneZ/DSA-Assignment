/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#include "List.h"
#include <stdexcept>
#include <functional>
using namespace std;

/**
 * Node Constructor
 * Process: Initializes a new node with a given value and sets the next pointer to nullptr.
 * Precondition: A value of type T must be provided.
 * Postcondition: A new Node object is created, and its `data` is set to the provided value, while `next` is initialized to nullptr.
 */
template <typename T>
List<T>::Node::Node(T value) : data(value), next(nullptr) {}


/**
 * List Constructor
 * Process: Initializes an empty list by setting the head to nullptr and the size to 0.
 * Precondition: None.
 * Postcondition: An empty List object is created with no elements.
 */
template <typename T>
List<T>::List() : head(nullptr), size(0) {}


/**
 * List Destructor
 * Process: Deallocates all dynamically allocated memory in the list by calling the `clear` method.
 * Precondition: None.
 * Postcondition: All nodes in the list are deleted, and the list becomes empty.
 */
template <typename T>
List<T>::~List() {
    clear();
}


/**
 * Add Method
 * Process: Appends a new value to the end of the list. Dynamically allocates a new node and adjusts the pointers accordingly.
 * Precondition: A value of type T must be provided.
 * Postcondition: The new value is added to the list, and the size is incremented by 1.
 */
template <typename T>
void List<T>::add(const T& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
    }
    else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    size++;
}


/**
 * Clear Method
 * Process: Deletes all nodes in the list and frees dynamically allocated memory.
 * Precondition: None.
 * Postcondition: The list is empty, and all previously allocated nodes are deallocated.
 */
template <typename T>
void List<T>::clear() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    size = 0;
}

/**
 * Sort Method
 * Sorts the list using a custom comparator.
 */
template <typename T>
void List<T>::sort(function<bool(const T&, const T&)> comparator) {
    if (!head || !head->next) return; // Empty or single-element list

    for (Node* i = head; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {
            if (comparator(j->data, i->data)) {
                std::swap(i->data, j->data);
            }
        }
    }
}

template <typename T>
Iterator<T>* List<T>::createIterator() const {
    return new ListIterator(head);
}

/**
 * Iterator Constructor
 * Process: Initializes the iterator to point to a given node in the list.
 * Precondition: A pointer to a valid node (or nullptr) must be provided.
 * Postcondition: An Iterator object is created that starts at the provided node.
 */
template <typename T>
List<T>::ListIterator::ListIterator(Node* start) : current(start) {}

template <typename T>
bool List<T>::ListIterator::hasNext() const {
    return current != nullptr;
}

/**
 * Next Method
 * Returns the next element in the list.
 */
template <typename T>
T List<T>::ListIterator::next() {
    if (!current) {
        throw std::out_of_range("No more elements");
    }
    T value = current->data;
    current = current->next;
    return value;
}

