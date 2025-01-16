/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/

#include "Map.h"

/**
 * Pair Constructor
 * Process: Initializes a Pair with the provided key and value.
 * Precondition: A key of type K and a value of type V must be provided.
 * Postcondition: A Pair object is created with the given key and value.
 */
template <typename K, typename V>
Map<K, V>::Pair::Pair(K key, V value) : key(key), value(value) {}


/**
 * Map Constructor
 * Process: Initializes an empty map.
 * Precondition: None.
 * Postcondition: A Map object is created with no elements.
 */
template <typename K, typename V>
Map<K, V>::Map() {}


/**
 * Map Destructor
 * Process: Deletes all dynamically allocated memory and clears the map.
 * Precondition: None.
 * Postcondition: All pairs in the map are deleted, and the map becomes empty.
 */
template <typename K, typename V>
Map<K, V>::~Map() {
    clear();
}


/**
 * Insert Method
 * Process: Adds a key-value pair to the map if the key does not already exist.
 * Precondition: A key of type K and a value of type V must be provided.
 * Postcondition: The key-value pair is added to the map if the key was not already present.
 */
template <typename K, typename V>
void Map<K, V>::insert(const K& key, const V& value) {
    if (!contains(key)) {
        data.add(new Pair(key, value));
    }
}


/**
 * Contains Method
 * Process: Checks whether a key exists in the map.
 * Precondition: A key of type K must be provided.
 * Postcondition: Returns true if the key exists, false otherwise.
 */
template <typename K, typename V>
bool Map<K, V>::contains(const K& key) const {
    for (auto iterator = data.createIterator(); iterator->hasNext();) {
        Pair* pair = iterator->next();
        if (pair->key == key) {
            delete iterator;
            return true;
        }
    }
    return false;
}

/**
 * Get Method
 * Process: Retrieves the value associated with a given key.
 * Precondition: A key of type K must be provided.
 * Postcondition: Returns the value associated with the key if it exists, or throws an exception if the key is not found.
 */
template <typename K, typename V>
V Map<K, V>::get(const K& key) const {
    for (auto iterator = data.createIterator(); iterator->hasNext();) {
        Pair* pair = iterator->next();
        if (pair->key == key) {
            delete iterator;
            return pair->value;
        }
    }
    throw std::runtime_error("Key not found");
}


/**
 * Clear Method
 * Process: Deletes all key-value pairs in the map and clears the internal list.
 * Precondition: None.
 * Postcondition: All pairs in the map are deleted, and the map becomes empty.
 */
template <typename K, typename V>
void Map<K, V>::clear() {
    for (auto iterator = data.createIterator(); iterator->hasNext();) {
        delete iterator->next();
    }
    data.clear();
}


/**
 * Iterator Constructor
 * Process: Initializes the iterator to point to a given position in the internal list.
 * Precondition: A valid List<Pair*>::Iterator must be provided.
 * Postcondition: An Iterator object is created that starts at the provided position.
 */
template <typename K, typename V>
Iterator<typename Map<K, V>::Pair*>* Map<K, V>::createIterator() const {
    return new MapIterator(data.createIterator());
}


/**
 * MapIterator Constructor
 * Wraps a List iterator.
 */
template <typename K, typename V>
Map<K, V>::MapIterator::MapIterator(Iterator<Pair*>* iterator) : listIterator(iterator) {}

/**
 * MapIterator Destructor
 * Deletes the internal iterator.
 */
template <typename K, typename V>
Map<K, V>::MapIterator::~MapIterator() {
    delete listIterator;
}

/**
 * Has Next Method
 * Checks if there are more elements in the map.
 */
template <typename K, typename V>
bool Map<K, V>::MapIterator::hasNext() const {
    return listIterator->hasNext();
}

/**
 * Next Method
 * Returns the next key-value pair in the map.
 */
template <typename K, typename V>
typename Map<K, V>::Pair* Map<K, V>::MapIterator::next() {
    return listIterator->next();
}
