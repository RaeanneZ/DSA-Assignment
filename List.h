/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#pragma once

#include "Iterator.h"
#include <stdexcept>
#include <functional>
#include <iostream>
using namespace std;

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head;
    int size;

public:
    /**
    * Constructor
    * Process: Initializes an empty linked list.
    * Precondition: None.
    * Postcondition: A new `List` object is created with `head = nullptr` and `size = 0`.
    */
    List() : head(nullptr), size(0) {}


    /**
    * Copy Constructor
    * Process: Creates a deep copy of another `List` object.
    * Precondition: `other` must be a valid `List` object.
    * Postcondition: A new `List` object is created with the same elements as `other`.
    */
    List(const List& other) : head(nullptr), size(0) {
        Node* current = other.head;
        while (current) {
            add(current->data); // Use the `add` method to copy data
            current = current->next;
        }
    }


    /**
    * Assignment Operator
    * Process: Clears the current list and copies elements from another `List` object.
    * Precondition: `other` must be a valid `List` object.
    * Postcondition: The current list is replaced with a deep copy of `other`.
    */
    List& operator=(const List& other) {
        if (this == &other) return *this; // Self-assignment check

        clear(); // Clear existing data
        Node* current = other.head;
        while (current) {
            add(current->data); // Use the `add` method to copy data
            current = current->next;
        }
        return *this;
    }


    /**
    * Destructor
    * Process: Calls `clear()` to free all dynamically allocated nodes.
    * Precondition: None.
    * Postcondition: All nodes in the list are deleted.
    */
    ~List() { clear(); }


    /**
    * Adds an element to the list.
    * Process: Appends the element at the end of the list.
    * Precondition: If `T` is a pointer type, `value` should not be `nullptr`.
    * Postcondition: A new node containing `value` is added to the list.
    */
    void add(const T& value) {
        if constexpr (is_pointer<T>::value) { // Only check for nullptr if T is a pointer
            if (value == nullptr) return; // Skip if value is nullptr
        }

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
    * Checks if a value exists in the list.
    * Process: Iterates through the list to find `value`.
    * Precondition: `value` must be a valid type that supports comparison.
    * Postcondition: Returns `true` if the value exists, otherwise returns `false`.
    */
    bool contains(const T& value) const {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    /**
    * Removes the first occurrence of the specified value from the list.
    * @param value The value to be removed.
    * Process: Traverses the list, finds the node containing the value, and removes it.
    * Precondition: The list must be initialized and the value should be comparable.
    * Postcondition: If the value exists in the list, it is removed, and the list size is updated.
    */
    void remove(const T& value) {
        if (!head) {
            cout << "The list is empty. Nothing to remove.\n";
            return;
        }

        // Special case: Removing the head of the list
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return;
        }

        // Traverse the list to find the node to remove
        Node* current = head;
        Node* previous = nullptr;

        while (current) {
            if (current->data == value) {
                previous->next = current->next; // Skip the current node
                delete current;
                size--;
                return;
            }
            previous = current;
            current = current->next;
        }

        // If the value was not found
        cout << "Value not found in the list.\n";
    }


    /**
    * Clears all elements from the list.
    * Process: Iterates through the list, deletes each node, and resets `head` and `size`.
    * Precondition: None.
    * Postcondition: The list becomes empty.
    */
    void clear() {
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
    * Sorts the list using a given comparison function.
    * Process: Calls one of the implemented sorting algorithms (e.g., quick sort).
    * Precondition: `comparator` must be a valid comparison function.
    * Postcondition: The list elements are sorted in ascending order based on `comparator`.
    */
    void sort(function<bool(const T&, const T&)> comparator) {
        //bubbleSort(comparator);
        //selectionSort(comparator);
        //insertionSort(comparator);
        //mergeSort(comparator);
        quickSort(comparator);
    }


    /**
    * Sorts the list using the bubble sort algorithm.
    * Process: Repeatedly swaps adjacent elements if they are in the wrong order.
    * Precondition: `comparator` must be a valid comparison function.
    * Postcondition: The list elements are sorted in ascending order.
    */
    void bubbleSort(function<bool(const T&, const T&)> comparator) {
        if (!head || !head->next) return; // Empty or single-element list

        for (Node* i = head; i != nullptr; i = i->next) {
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (comparator(j->data, i->data)) {
                    swap(i->data, j->data);
                }
            }
        }
    }

    
    /**
    * Sorts the list using the selection sort algorithm.
    * Process: Finds the smallest element in the unsorted portion and swaps it with the first element.
    * Precondition: `comparator` must be a valid comparison function.
    * Postcondition: The list elements are sorted in ascending order.
    */
    void selectionSort(function<bool(const T&, const T&)> comparator) {
        for (Node* i = head; i && i->next; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j; j = j->next) {
                if (comparator(j->data, minNode->data)) {
                    minNode = j;
                }
            }
            if (minNode != i) {
                swap(i->data, minNode->data);
            }
        }
    }


    /**
    * Sorts the list using the insertion sort algorithm.
    * Process: Moves elements one by one to their correct position.
    * Precondition: `comparator` must be a valid comparison function.
    * Postcondition: The list elements are sorted in ascending order.
    */
    void insertionSort(function<bool(const T&, const T&)> comparator) {
        if (!head || !head->next) return;
        Node* sorted = nullptr;
        Node* current = head;
        while (current) {
            Node* next = current->next;
            if (!sorted || comparator(current->data, sorted->data)) {
                current->next = sorted;
                sorted = current;
            }
            else {
                Node* temp = sorted;
                while (temp->next && !comparator(current->data, temp->next->data)) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }
        head = sorted;
    }

    /**
    * Merges two sorted linked lists into one sorted list.
    * Process: Recursively compares the nodes of two lists and links them in sorted order.
    * Precondition: `left` and `right` must be valid pointers to sorted linked lists.
    * Postcondition: Returns a pointer to the merged sorted list.
    */
    Node* merge(Node* left, Node* right, function<bool(const T&, const T&)> comparator) {
        if (!left) return right;
        if (!right) return left;
        if (comparator(left->data, right->data)) {
            left->next = merge(left->next, right, comparator);
            return left;
        }
        else {
            right->next = merge(left, right->next, comparator);
            return right;
        }
    }

    /**
    * Helper function to perform MergeSort on the linked list.
    * Process: Recursively splits the list into two halves, sorts them, and merges the sorted halves.
    * Precondition: `start` must be a valid pointer within the list.
    * Postcondition: Returns a pointer to the sorted linked list.
    */
    Node* mergeSortHelper(Node* start, function<bool(const T&, const T&)> comparator) {
        if (!start || !start->next) return start;
        Node* slow = start, * fast = start->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node* mid = slow->next;
        slow->next = nullptr;
        Node* left = mergeSortHelper(start, comparator);
        Node* right = mergeSortHelper(mid, comparator);
        return merge(left, right, comparator);
    }


    /**
    * Sorts the list using the merge sort algorithm.
    * Process: Recursively divides the list into two halves, sorts them, and merges them.
    * Precondition: `comparator` must be a valid comparison function.
    * Postcondition: The list elements are sorted in ascending order.
    */
    void mergeSort(function<bool(const T&, const T&)> comparator) {
        head = mergeSortHelper(head, comparator);
    }


    /**
    * Partitions the list around a pivot node for QuickSort.
    * Process: Moves elements smaller than the pivot to the left and elements greater than the pivot to the right.
    * Precondition: `low` and `high` must be valid pointers within the list.
    * Postcondition: Returns a pointer to the pivot node after partitioning.
    */
    Node* partition(Node* low, Node* high, function<bool(const T&, const T&)> comparator) {
        T pivot = high->data;
        Node* i = low;
        for (Node* j = low; j != high; j = j->next) {
            if (comparator(j->data, pivot)) {
                swap(i->data, j->data);
                i = i->next;
            }
        }
        swap(i->data, high->data);
        return i;
    }

    /**
    * Helper function to perform QuickSort on the linked list.
    * Process: Recursively partitions the list and sorts the left and right segments.
    * Precondition: `low` and `high` must be valid pointers within the list.
    * Postcondition: The list is sorted in ascending order based on the comparator function.
    */
    void quickSortHelper(Node* low, Node* high, function<bool(const T&, const T&)> comparator) {
        if (!low || !high || low == high || low == high->next) return;

        Node* pivot = partition(low, high, comparator);

        // Find the node just before the pivot
        Node* temp = low;
        Node* prev = nullptr;
        while (temp != pivot && temp != nullptr) {
            prev = temp;
            temp = temp->next;
        }

        // Disconnect the left part from the pivot
        if (prev) prev->next = nullptr;

        // Recurse on the left part
        if (temp != low) {
            quickSortHelper(low, prev, comparator);
            if (prev) prev->next = pivot;  // Reconnect after sorting
        }

        // Recurse on the right part
        quickSortHelper(pivot->next, high, comparator);
    }


    /**
    * Sorts the list using the quick sort algorithm.
    * Process: Selects a pivot element, partitions the list, and recursively sorts the partitions.
    * Precondition: `comparator` must be a valid comparison function.
    * Postcondition: The list elements are sorted in ascending order.
    */
    void quickSort(function<bool(const T&, const T&)> comparator) {
        if (!head) return;
        Node* high = head;
        while (high->next) high = high->next;
        quickSortHelper(head, high, comparator);
    }


    /**
    * Returns the number of elements in the list.
    * Process: Returns the value of `size`.
    * Precondition: None.
    * Postcondition: Returns the total number of nodes in the list.
    */
    int getSize() const {
        return size;
    }


    /**
    * Checks if the list is empty.
    * Process: Returns `true` if `head` is `nullptr` or `size == 0`.
    * Precondition: None.
    * Postcondition: Returns `true` if the list is empty, otherwise `false`.
    */
    bool isEmpty() const {
        return head == nullptr; // or size == 0
    }


    /**
    * Prints the elements of the list.
    * Process: Iterates through the list and prints each element.
    * Precondition: `T` must support the `<<` operator.
    * Postcondition: The list elements are displayed in the console.
    */
    void print() const {
        Node* current = head;
        cout << "List elements: ";
        while (current) {
            cout << current->data << " "; // Assumes T supports the << operator
            current = current->next;
        }
        cout << endl;
    }

    /**
    * Returns a pointer to the head node.
    * Process: Returns the pointer to the first node in the list.
    * Precondition: None.
    * Postcondition: Returns a pointer to the head node.
    */
    Node* getHead() const {
        return head;
    }

    /**
    * Sets the head node.
    * Process: Updates the `head` pointer to `newHead`.
    * Precondition: `newHead` must be a valid `Node*`.
    * Postcondition: The head of the list is updated.
    */
    void setHead(Node* newHead) {
        head = newHead;
    }

    /**
    * Decreases the size counter by 1.
    * Process: Decrements the `size` variable.
    * Precondition: The list must contain at least one element.
    * Postcondition: The size of the list is reduced by one.
    */
    void decrementSize() {
        size--;
    }


    /**
    * Iterator for traversing the list.
    * Process: Maintains a pointer to the current node and moves to the next node on `next()`.
    * Precondition: `start` must be a valid pointer to the head node or `nullptr`.
    * Postcondition: Allows iteration over the list elements.
    */
    class ListIterator : public Iterator<T> {
    private:
        Node* current;

    public:
        /**
        * Constructor for ListIterator.
        * Process: Initializes the iterator by setting `current` to the head of the list.
        * Precondition: `start` must be a valid pointer to the head node of a `List` or `nullptr`.
        * Postcondition: The iterator is initialized with the starting position.
        */
        ListIterator(Node* start) : current(start) {}


        /**
        * Checks if there are more elements to iterate over in the list.
        * Process: Returns `true` if `current` is not `nullptr`, indicating that more elements exist.
        * Precondition: None.
        * Postcondition: Returns `true` if there are more elements, otherwise returns `false`.
        */
        bool hasNext() const override {
            return current != nullptr; //Ensure current node is valid
        }


        /**
        * Retrieves the next element in the list.
        * Process: Returns the current element's data and advances to the next node.
        * Precondition: `hasNext()` must return `true`; otherwise, an exception is thrown.
        * Postcondition: Returns the next element in the list and moves the iterator forward.
        */
        T next() override {
            if (!current) {
                throw out_of_range("No more elements");
            }

            T value = current->data;
            current = current->next;

            return value;
        }
    };


    /**
    * Creates an iterator for the list.
    * Process: Instantiates a `ListIterator` object with the head node.
    * Precondition: None.
    * Postcondition: Returns an iterator for sequential traversal of the list.
    */
    Iterator<T>* createIterator() const {
        if (!head) {
            /*cout << "Iterator created for an empty list" << endl;*/
        }

        return new ListIterator(head);
    }
};