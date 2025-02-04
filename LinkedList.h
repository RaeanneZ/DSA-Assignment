#pragma once

#include "Iterator.h"
#include <stdexcept>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    int listSize;

public:
    LinkedList() : head(nullptr), listSize(0) {}

    // Deep copy constructor
    LinkedList(const LinkedList& other) : head(nullptr), listSize(0) {
        Node* temp = other.head;
        while (temp) {
            add(temp->data);
            temp = temp->next;
        }
    }

    // Assignment operator
    LinkedList& operator=(const LinkedList& other) {
        if (this == &other) return *this;
        clear();
        Node* temp = other.head;
        while (temp) {
            add(temp->data);
            temp = temp->next;
        }
        return *this;
    }

    ~LinkedList() { clear(); }

    void add(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        listSize++;
    }

    void remove(const T& value) {
        if (!head) return;
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            listSize--;
            return;
        }

        Node* prev = nullptr;
        Node* current = head;
        while (current) {
            if (current->data == value) {
                prev->next = current->next;
                delete current;
                listSize--;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    bool contains(const T& value) const {
        Node* temp = head;
        while (temp) {
            if (temp->data == value) return true;
            temp = temp->next;
        }
        return false;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        listSize = 0;
    }

    int getSize() const { return listSize; }

    bool isEmpty() const { return head == nullptr; }

    class LinkedListIterator : public Iterator<T> {
    private:
        Node* current;
    public:
        LinkedListIterator(Node* start) : current(start) {}

        bool hasNext() const override { return current != nullptr; }

        T next() override {
            if (!current) throw std::out_of_range("No more elements in list.");
            T value = current->data;
            current = current->next;
            return value;
        }
    };

    Iterator<T>* createIterator() const {
        return new LinkedListIterator(head);
    }
};
