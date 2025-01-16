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
    Map();
    ~Map();

    void insert(const K& key, const V& value);
    bool contains(const K& key) const;
    V get(const K& key) const;
    void clear();

    Iterator<Pair*>* createIterator() const;

    class MapIterator : public Iterator<Pair*> {
    private:
        Iterator<Pair*>* listIterator;

    public:
        MapIterator(Iterator<Pair*>* iterator);
        ~MapIterator();
        bool hasNext() const override;
        Pair* next() override;
    };
};

