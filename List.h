/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#pragma once
#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

template <typename T>
class List
{
private:
    struct Node {
        T data;
        Node* next;
        Node(T value);
    };

    Node* head;
    int size;

public:
    List();
    ~List();

    void add(const T& value);
    T* find(bool (*compare)(const T&));
    void sort(bool (*compare)(const T&, const T&) = nullptr);
    void clear();

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node);
        bool operator!=(const Iterator& other) const;
        T& operator*() const;
        T* operator->() const;
        Iterator& operator++();
    };

    Iterator begin() const;
    Iterator end() const;
};

#include "List.cpp" // Include implementation
#endif // LIST_H