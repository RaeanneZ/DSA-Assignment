/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#ifndef MAP_H
#define MAP_H

#include "List.h"
#include <stdexcept> // For std::runtime_error

template <typename K, typename V>
class Map {
private:
    struct Pair {
        K key;
        V value;
        Pair(K key, V value);
    };

    List<Pair*> data; // List to store key-value pairs

public:
    Map();
    ~Map();

    void insert(const K& key, const V& value);
    bool contains(const K& key) const;
    V get(const K& key) const;
    void remove(const K& key);
    void clear();

    class Iterator {
    private:
        typename List<Pair*>::Iterator it;

    public:
        Iterator(typename List<Pair*>::Iterator iter);
        bool operator!=(const Iterator& other) const;
        Pair* operator*() const;
        Pair* operator->() const;
        Iterator& operator++();
    };

    Iterator begin() const;
    Iterator end() const;

private:
    Pair* find(const K& key) const;
};

#include "Map.cpp" // Include the template implementation
#endif // MAP_H

