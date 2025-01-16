/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#include "List.h"

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
 * Find Method
 * Process: Traverses the list to find the first element that matches the condition specified by the `compare` function.
 * Precondition: A valid `compare` function must be provided. It should accept a `const T&` and return a boolean.
 * Postcondition: Returns a pointer to the first matching element if found, or nullptr if no match is found.
 */
template <typename T>
T* List<T>::find(bool (*compare)(const T&)) {
    Node* temp = head;
    while (temp) {
        if (compare(temp->data)) {
            return &temp->data;
        }
        temp = temp->next;
    }
    return nullptr;
}


/**
 * Sort Method
 * Process: Sorts the list in ascending order by default or uses a custom comparison function if provided.
 * Precondition: The `compare` function (if provided) should accept two `const T&` values and return a boolean indicating order.
 * Postcondition: The list is sorted, and the relative order of elements is updated based on the sorting criteria.
 */
template <typename T>
void List<T>::sort(bool (*compare)(const T&, const T&)) {
    if (!head || !head->next) return;
    for (Node* i = head; i; i = i->next) {
        for (Node* j = i->next; j; j = j->next) {
            if ((compare && compare(j->data, i->data)) || (!compare && j->data < i->data)) {
                T temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}


/**
 * Clear Method
 * Process: Deletes all nodes in the list and frees dynamically allocated memory.
 * Precondition: None.
 * Postcondition: The list is empty, and all previously allocated nodes are deallocated.
 */
template <typename T>
void List<T>::clear() {
    Node* temp = head;
    while (temp) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
    head = nullptr;
}


/**
 * Iterator Constructor
 * Process: Initializes the iterator to point to a given node in the list.
 * Precondition: A pointer to a valid node (or nullptr) must be provided.
 * Postcondition: An Iterator object is created that starts at the provided node.
 */
template <typename T>
List<T>::Iterator::Iterator(Node* node) : current(node) {}


/**
 * Iterator Not Equal Operator
 * Process: Compares two iterators for inequality based on their current positions.
 * Precondition: Both iterators must be initialized.
 * Postcondition: Returns true if the iterators point to different nodes, false otherwise.
 */
template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}


/**
 * Iterator Dereference Operator
 * Process: Accesses the data at the current node.
 * Precondition: The iterator must point to a valid node.
 * Postcondition: Returns a reference to the data stored at the current node.
 */
template <typename T>
T& List<T>::Iterator::operator*() const {
    return current->data;
}


/**
 * Iterator Arrow Operator
 * Process: Provides access to the data at the current node via pointer semantics.
 * Precondition: The iterator must point to a valid node.
 * Postcondition: Returns a pointer to the data stored at the current node.
 */
template <typename T>
T* List<T>::Iterator::operator->() const {
    return &current->data;
}


/**
 * Iterator Increment Operator
 * Process: Moves the iterator to the next node in the list.
 * Precondition: The iterator must point to a valid node.
 * Postcondition: The iterator now points to the next node, or nullptr if the end of the list is reached.
 */
template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    if (current) {
        current = current->next;
    }
    return *this;
}


/**
 * Begin Method
 * Process: Returns an iterator pointing to the first node in the list.
 * Precondition: None.
 * Postcondition: An iterator pointing to the head of the list is returned.
 */
template <typename T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(head);
}


/**
 * End Method
 * Process: Returns an iterator pointing to the end of the list (nullptr).
 * Precondition: None.
 * Postcondition: An iterator pointing to nullptr is returned.
 */
template <typename T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator(nullptr);
}
