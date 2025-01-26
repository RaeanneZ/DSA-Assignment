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
    Map() {}
    ~Map() { clear(); }

    void insert(const K& key, const V& value) {
        if (contains(key)) {
            throw invalid_argument("Duplicate key");
        }
        data.add(new Pair(key, value));
    }

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

    V get(const K& key) const {
        auto it = data.createIterator();
        while (it->hasNext()) {
            Pair* pair = it->next();
            if (pair->key == key) {
                V value = pair->value;
                delete it;
                return value;
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



    void clear() {
        auto it = data.createIterator();
        while (it->hasNext()) {
            delete it->next();
        }
        delete it;
        data.clear();
    }

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

    Iterator<Pair*>* createIterator() const {
        return new MapIterator(data.createIterator());
    }
};
