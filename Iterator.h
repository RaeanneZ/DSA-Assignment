/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#pragma once

template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;

    // Check if there is a next element
    virtual bool hasNext() const = 0;

    // Get the next element
    virtual T next() = 0;
};

template <typename T>
class Iterable {
public:
    virtual ~Iterable() = default;

    // Return an iterator for the collection
    virtual Iterator<T>* createIterator() const = 0;
};

