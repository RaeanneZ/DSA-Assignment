#pragma once

#include "Iterator.h"
#include <stdexcept>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* topNode;
    int stackSize;

public:
    Stack() : topNode(nullptr), stackSize(0) {}

    // Deep copy constructor
    Stack(const Stack& other) : topNode(nullptr), stackSize(0) {
        Node* temp = other.topNode;
        Stack<T> tempStack;
        while (temp) {
            tempStack.push(temp->data);
            temp = temp->next;
        }

        while (!tempStack.isEmpty()) {
            push(tempStack.pop());
        }
    }

    // Assignment operator
    Stack& operator=(const Stack& other) {
        if (this == &other) return *this;
        clear();
        Node* temp = other.topNode;
        Stack<T> tempStack;
        while (temp) {
            tempStack.push(temp->data);
            temp = temp->next;
        }

        while (!tempStack.isEmpty()) {
            push(tempStack.pop());
        }

        return *this;
    }

    ~Stack() { clear(); }

    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        stackSize++;
    }

    T pop() {
        if (isEmpty()) throw std::underflow_error("Stack underflow.");
        Node* temp = topNode;
        T value = temp->data;
        topNode = topNode->next;
        delete temp;
        stackSize--;
        return value;
    }

    bool contains(const T& value) const {
        Node* temp = topNode;
        while (temp) {
            if (temp->data == value) return true;
            temp = temp->next;
        }
        return false;
    }

    void clear() {
        while (!isEmpty()) pop();
    }

    int getSize() const { return stackSize; }

    bool isEmpty() const { return topNode == nullptr; }

    class StackIterator : public Iterator<T> {
    private:
        Node* current;
    public:
        StackIterator(Node* start) : current(start) {}

        bool hasNext() const override { return current != nullptr; }

        T next() override {
            if (!current) throw std::out_of_range("No more elements in stack.");
            T value = current->data;
            current = current->next;
            return value;
        }
    };

    Iterator<T>* createIterator() const {
        return new StackIterator(topNode);
    }
};
