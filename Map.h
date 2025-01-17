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
