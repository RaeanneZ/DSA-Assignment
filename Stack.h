#pragma once

#include "Iterator.h"
#include <stdexcept>

/**
 * Stack Data Structure
 * Template implementation for a Stack using a singly linked list.
 */
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
        if (isEmpty()) throw std::underflow_error("Stack underflow: Attempted to pop from an empty stack.");
        Node* temp = topNode;
        T value = temp->data;
        topNode = topNode->next;
        delete temp;
        stackSize--;
        return value;
    }

    T peek() const {
        if (isEmpty()) throw std::underflow_error("Stack is empty.");
        return topNode->data;
    }

    void remove(const T& value) {
        Node* current = topNode;
        Node* prev = nullptr;
        while (current) {
            if (current->data == value) {
                if (prev) {
                    prev->next = current->next;
                }
                else {
                    topNode = current->next;
                }
                delete current;
                stackSize--;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    bool contains(const T& value) const {
        Node* current = topNode;
        while (current) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }

    void clear() {
        while (!isEmpty()) pop();
    }

    bool isEmpty() const { return topNode == nullptr; }

    int getSize() const { return stackSize; }

    class StackIterator : public Iterator<T> {
    private:
        Node* current;
    public:
        StackIterator(Node* start) : current(start) {}

        bool hasNext() const override {
            return current != nullptr;
        }

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
