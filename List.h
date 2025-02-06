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
    List() : head(nullptr), size(0) {}
    
    // Copy constructor for deep copy
    List(const List& other) : head(nullptr), size(0) {
        Node* current = other.head;
        while (current) {
            add(current->data); // Use the `add` method to copy data
            current = current->next;
        }
    }

    // Assignment operator
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

    ~List() { clear(); }

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

    void sort(function<bool(const T&, const T&)> comparator) {
        if (!head || !head->next) return; // Empty or single-element list

        for (Node* i = head; i != nullptr; i = i->next) {
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (comparator(j->data, i->data)) {
                    swap(i->data, j->data);
                }
            }
        }
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return head == nullptr; // or size == 0
    }

    void print() const {
        Node* current = head;
        cout << "List elements: ";
        while (current) {
            cout << current->data << " "; // Assumes T supports the << operator
            current = current->next;
        }
        cout << endl;
    }

    // Accessor for head (needed for integration with other classes)
    Node* getHead() const {
        return head;
    }

    // Mutator for head (needed for integration with other classes)
    void setHead(Node* newHead) {
        head = newHead;
    }

    // Decrement size (needed for integration with other classes)
    void decrementSize() {
        size--;
    }

    class ListIterator : public Iterator<T> {
    private:
        Node* current;

    public:
        ListIterator(Node* start) : current(start) {}

        bool hasNext() const override {
            return current != nullptr; //Ensure current node is valid
        }

        T next() override {
            if (!current) {
                throw out_of_range("No more elements");
            }
      
            T value = current->data; 
            current = current->next;
           
            return value;
        }
    };

    Iterator<T>* createIterator() const {
        if (!head) {
            /*cout << "Iterator created for an empty list" << endl;*/
        }

        return new ListIterator(head);
    }
};