/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#pragma once

#include "List.h"
#include "Iterator.h"
#include <stdexcept>

template <typename K, typename V>
class Map {
private:
    struct Pair {
        K key;
        V value;
        Pair(K key, V value) : key(key), value(value) {}
    };

    List<Pair*> data;

public:
    /**
    * Constructor
    * Process: Initializes an empty map.
    * Precondition: None.
    * Postcondition: A new `Map` object is created with an empty list.
    */
    Map() {}

    /**
    * Destructor
    * Process: Calls `clear()` to free dynamically allocated memory for all key-value pairs.
    * Precondition: None.
    * Postcondition: All elements in the map are deleted.
    */
    ~Map() { clear(); }


    /**
    * Inserts a key-value pair into the map.
    * Process: Checks if the key already exists; if not, creates a new key-value pair and adds it to the list.
    * Precondition: The key must be unique; otherwise, an exception is thrown.
    * Postcondition: The key-value pair is added to the map.
    */
    void insert(const K& key, const V& value) {
        if (contains(key)) {
            throw invalid_argument("Duplicate key");
        }
        data.add(new Pair(key, value));
    }


    /**
    * Checks if a key exists in the map.
    * Process: Iterates through the list to find the key.
    * Precondition: The key must be a valid type that supports comparison.
    * Postcondition: Returns `true` if the key exists, otherwise returns `false`.
    */
    bool contains(const K& key) const {
        auto it = data.createIterator();
        while (it->hasNext()) {
            Pair* pair = it->next();
            if (pair->key == key) {
                delete it;
                return true;
            }
        }
        delete it;
        return false;
    }


    /**
    * Retrieves the value associated with a key.
    * Process: Searches for the key in the list and returns the associated value.
    * Precondition: The key must exist in the map; otherwise, an exception is thrown.
    * Postcondition: Returns a reference to the value associated with the key.
    */
    V& get(const K& key) { // Non-const version
        auto it = data.createIterator();
        while (it->hasNext()) {
            Pair* pair = it->next();
            if (pair->key == key) {
                delete it;
                return pair->value; // Return by reference
            }
        }
        delete it;
        throw invalid_argument("Key not found");
    }


    /**
    * Retrieves the value associated with a key (const version).
    * Process: Searches for the key in the list and returns the associated value.
    * Precondition: The key must exist in the map; otherwise, an exception is thrown.
    * Postcondition: Returns a constant reference to the value associated with the key.
    */
    const V& get(const K& key) const { // Const version
        auto it = data.createIterator();
        while (it->hasNext()) {
            Pair* pair = it->next();
            if (pair->key == key) {
                delete it;
                return pair->value; // Return by reference
            }
        }
        delete it;
        throw invalid_argument("Key not found");
    }


    /**
   * Removes the pair with the specified key from the map.
   * @param key The key of the pair to be removed.
   * Process: Traverses the underlying list, finds the pair with the matching key, and removes it.
   * Precondition: The map must be initialized.
   * Postcondition: If the key exists in the map, its associated pair is removed, and memory is freed.
   */
    void remove(const K& key) {
        auto it = data.createIterator();
        auto previous = static_cast<decltype(data.getHead())>(nullptr); // Pointer to the previous node
        auto current = data.getHead(); // Pointer to the head node

        while (current) {
            Pair* pair = current->data;

            if (pair->key == key) {
                // Key found, remove the pair
                if (previous) {
                    previous->next = current->next; // Skip the current node
                }
                else {
                    data.setHead(current->next); // Update the head if the first node matches
                }

                delete pair; // Free the memory of the pair
                delete current; // Free the memory of the node
                data.decrementSize(); // Update the size of the list
                delete it;
                return;
            }

            // Move to the next node
            previous = current;
            current = current->next;
        }

        delete it;
        throw invalid_argument("Key not found in the map");
    }


    /**
    * Clears all elements from the map.
    * Process: Iterates through the list, deletes all key-value pairs, and clears the list.
    * Precondition: None.
    * Postcondition: The map becomes empty.
    */
    void clear() {
        auto it = data.createIterator();
        while (it->hasNext()) {
            delete it->next();
        }
        delete it;
        data.clear();
    }


    /**
    * Returns the number of key-value pairs in the map.
    * Process: Returns the size of the list.
    * Precondition: None.
    * Postcondition: Returns the total number of elements in the map.
    */
    int getSize() const {
        return data.getSize();
    }


    /**
    * Prints all key-value pairs in the map.
    * Process: Iterates through the list and prints each key and value.
    * Precondition: The key and value types must support the `<<` operator.
    * Postcondition: All key-value pairs are displayed in the console.
    */
    void print() const {
        auto it = data.createIterator();
        while (it->hasNext()) {
            Pair* pair = it->next();
            cout << "Key: " << pair->key << " | Value: " << pair->value << endl;
        }
        delete it;
    }


    /**
    * Iterator for traversing the map.
    * Process: Uses a `List` iterator to iterate over key-value pairs.
    * Precondition: The map must be initialized.
    * Postcondition: Allows iteration over the map's key-value pairs.
    */
    class MapIterator : public Iterator<Pair*> {
    private:
        Iterator<Pair*>* listIterator;

    public:
        MapIterator(Iterator<Pair*>* iterator) : listIterator(iterator) {}
        ~MapIterator() { delete listIterator; }

        bool hasNext() const override {
            return listIterator->hasNext();
        }

        Pair* next() override {
            return listIterator->next();
        }
    };

    /**
    * Creates an iterator for the map.
    * Process: Instantiates a `MapIterator` object with a list iterator.
    * Precondition: None.
    * Postcondition: Returns an iterator for sequential traversal of the map.
    */
    Iterator<Pair*>* createIterator() const {
        return new MapIterator(data.createIterator());
    }
};
