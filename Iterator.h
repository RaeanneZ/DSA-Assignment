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

    /**
     * Process: Checks if there is a next element in the collection.
     * Precondition: None.
     * Postcondition: Returns true if there are more elements, false otherwise.
     */
    virtual bool hasNext() const = 0;

    /**
     * Process: Retrieves the next element in the collection.
     * Precondition: The collection must have a next element.
     * Postcondition: Returns the next element and advances the iterator.
     */
    virtual T next() = 0;
};

/**
 * Iterable Interface
 * Defines a collection that can provide an iterator.
 */
template <typename T>
class Iterable {
public:
    virtual ~Iterable() = default;

    /**
     * Process: Creates an iterator for the collection.
     * Precondition: None.
     * Postcondition: Returns a new iterator for the collection.
     */
    virtual Iterator<T>* createIterator() const = 0;
};


