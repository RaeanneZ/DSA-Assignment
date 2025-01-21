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
        if (!value) return; // Skip if value is nullptr
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