#pragma once
#include "LinkedList.h"

template <typename T>
class Queue {
private:
    LinkedList<T> list;

public:
    void enqueue(const T& value) { list.add(value); }

    void dequeue() { if (list.getSize() > 0) list.remove(list.getSize() - 1); }

    T front() { return list.getSize() > 0 ? list.get(0) : T(); }

    bool isEmpty() { return list.getSize() == 0; }
};


