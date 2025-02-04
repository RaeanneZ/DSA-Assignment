#pragma once

#include "Iterator.h"
#include <stdexcept>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;
    int queueSize;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr), queueSize(0) {}

    // Deep copy constructor
    Queue(const Queue& other) : frontNode(nullptr), rearNode(nullptr), queueSize(0) {
        Node* temp = other.frontNode;
        while (temp) {
            enqueue(temp->data);
            temp = temp->next;
        }
    }

    // Assignment operator
    Queue& operator=(const Queue& other) {
        if (this == &other) return *this;
        clear();
        Node* temp = other.frontNode;
        while (temp) {
            enqueue(temp->data);
            temp = temp->next;
        }
        return *this;
    }

    ~Queue() { clear(); }

    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (!rearNode) {
            frontNode = rearNode = newNode;
        }
        else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        queueSize++;
    }

    T dequeue() {
        if (isEmpty()) throw std::underflow_error("Queue underflow.");
        Node* temp = frontNode;
        T value = temp->data;
        frontNode = frontNode->next;
        if (!frontNode) rearNode = nullptr;
        delete temp;
        queueSize--;
        return value;
    }

    void remove(const T& value) {
        if (!frontNode) return;

        if (frontNode->data == value) {
            dequeue();
            return;
        }

        Node* prev = nullptr;
        Node* current = frontNode;
        while (current) {
            if (current->data == value) {
                prev->next = current->next;
                if (current == rearNode) rearNode = prev;
                delete current;
                queueSize--;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    bool contains(const T& value) const {
        Node* temp = frontNode;
        while (temp) {
            if (temp->data == value) return true;
            temp = temp->next;
        }
        return false;
    }

    void clear() {
        while (!isEmpty()) dequeue();
    }

    int getSize() const { return queueSize; }

    bool isEmpty() const { return frontNode == nullptr; }

    class QueueIterator : public Iterator<T> {
    private:
        Node* current;
    public:
        QueueIterator(Node* start) : current(start) {}

        bool hasNext() const override { return current != nullptr; }

        T next() override {
            if (!current) throw std::out_of_range("No more elements in queue.");
            T value = current->data;
            current = current->next;
            return value;
        }
    };

    Iterator<T>* createIterator() const {
        return new QueueIterator(frontNode);
    }
};
