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
    List();
    ~List();

    void add(const T& value);
    void clear();
    void sort(function<bool(const T&, const T&)> comparator);
    Iterator<T>* createIterator() const;

    class ListIterator : public Iterator<T> {
    private:
        Node* current;

    public:
        ListIterator(Node* start);
        bool hasNext() const override;
        T next() override;
    };
};
