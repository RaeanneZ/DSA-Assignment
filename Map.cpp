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
    return find(key) != nullptr;
}


/**
 * Get Method
 * Process: Retrieves the value associated with a given key.
 * Precondition: A key of type K must be provided.
 * Postcondition: Returns the value associated with the key if it exists, or throws an exception if the key is not found.
 */
template <typename K, typename V>
V Map<K, V>::get(const K& key) const {
    Pair* pair = find(key);
    if (pair) {
        return pair->value;
    }
    throw std::runtime_error("Key not found");
}


/**
 * Remove Method
 * Process: Removes the key-value pair with the specified key from the map.
 * Precondition: A key of type K must be provided.
 * Postcondition: The key-value pair is removed if it exists, and the corresponding memory is deallocated.
 */
template <typename K, typename V>
void Map<K, V>::remove(const K& key) {
    auto it = data.begin();
    while (it != data.end()) {
        if ((*it)->key == key) {
            delete* it;              // Free the memory of the Pair.
            it = data.erase(it);     // Erase the node and move the iterator forward.
        }
        else {
            ++it;
        }
    }
}


/**
 * Clear Method
 * Process: Deletes all key-value pairs in the map and clears the internal list.
 * Precondition: None.
 * Postcondition: All pairs in the map are deleted, and the map becomes empty.
 */
template <typename K, typename V>
void Map<K, V>::clear() {
    auto it = data.begin();
    while (it != data.end()) {
        delete* it; // Free the memory of the Pair.
        ++it;
    }
    data.clear(); // Clear the underlying list.
}


/**
 * Iterator Constructor
 * Process: Initializes the iterator to point to a given position in the internal list.
 * Precondition: A valid List<Pair*>::Iterator must be provided.
 * Postcondition: An Iterator object is created that starts at the provided position.
 */
template <typename K, typename V>
Map<K, V>::Iterator::Iterator(typename List<Pair*>::Iterator iter) : it(iter) {}


/**
 * Iterator Not Equal Operator
 * Process: Compares two iterators for inequality.
 * Precondition: Both iterators must be initialized.
 * Postcondition: Returns true if the iterators point to different positions, false otherwise.
 */
template <typename K, typename V>
bool Map<K, V>::Iterator::operator!=(const Iterator& other) const {
    return it != other.it;
}


/**
 * Iterator Dereference Operator
 * Process: Accesses the current Pair object pointed to by the iterator.
 * Precondition: The iterator must point to a valid position.
 * Postcondition: Returns a reference to the Pair object.
 */
template <typename K, typename V>
typename Map<K, V>::Pair* Map<K, V>::Iterator::operator*() const {
    return *it;
}


/**
 * Iterator Arrow Operator
 * Process: Provides pointer-like access to the current Pair object.
 * Precondition: The iterator must point to a valid position.
 * Postcondition: Returns a pointer to the Pair object.
 */
template <typename K, typename V>
typename Map<K, V>::Pair* Map<K, V>::Iterator::operator->() const {
    return *it;
}


/**
 * Iterator Increment Operator
 * Process: Moves the iterator to the next position in the list.
 * Precondition: The iterator must point to a valid position.
 * Postcondition: The iterator now points to the next position or to the end of the list.
 */
template <typename K, typename V>
typename Map<K, V>::Iterator& Map<K, V>::Iterator::operator++() {
    ++it;
    return *this;
}


/**
 * Begin Method
 * Process: Returns an iterator pointing to the first Pair in the map.
 * Precondition: None.
 * Postcondition: An iterator pointing to the first element is returned.
 */
template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::begin() const {
    return Iterator(data.begin());
}


/**
 * End Method
 * Process: Returns an iterator pointing to the end of the map.
 * Precondition: None.
 * Postcondition: An iterator pointing past the last element is returned.
 */
template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::end() const {
    return Iterator(data.end());
}


/**
 * Find Method
 * Process: Searches for a key in the map and returns the corresponding Pair if found.
 * Precondition: A key of type K must be provided.
 * Postcondition: Returns a pointer to the Pair if the key is found, or nullptr if not found.
 */
template <typename K, typename V>
typename Map<K, V>::Pair* Map<K, V>::find(const K& key) const {
    for (auto it = data.begin(); it != data.end(); ++it) {
        if ((*it)->key == key) {
            return *it;
        }
    }
    return nullptr;
}
