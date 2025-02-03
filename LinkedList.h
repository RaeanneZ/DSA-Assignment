#pragma once
#include "Iterator.h"

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    LinkedList(const LinkedList& other) : head(nullptr), size(0) {
        Node* current = other.head;
        while (current) {
            add(current->data);
            current = current->next;
        }
    }

    ~LinkedList() { clear(); }

    void add(const T& value) {
        Node* newNode = new Node(value);
        if (!head) head = newNode;
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        size++;
    }

    void remove(const T& value) {
        Node* current = head, * prev = nullptr;
        while (current) {
            if (current->data == value) {
                if (prev) prev->next = current->next;
                else head = current->next;
                delete current;
                size--;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    bool contains(const T& value) const {
        Node* current = head;
        while (current) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }

    int getSize() const { return size; }

    class LinkedListIterator : public Iterator<T> {
    private:
        Node* current;
    public:
        LinkedListIterator(Node* start) : current(start) {}

        bool hasNext() const override { return current != nullptr; }

        T next() override {
            if (!current) throw out_of_range("No more elements");
            T value = current->data;
            current = current->next;
            return value;
        }
    };

    Iterator<T>* createIterator() const { return new LinkedListIterator(head); }
};

