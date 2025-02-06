#pragma once
#include "Iterator.h"
#include "List.h" 
#include <stdexcept>

/**
 * AVLTree: A self-balancing binary search tree.
 */
template <typename K, typename V>
class AVLTree {
private:
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        int height;

        Node(K key, V value) : key(key), value(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int height(Node* node) { return node ? node->height : 0; }

    Node* balance(Node* node) {
        int balanceFactor = getBalance(node);

        // Left Heavy
        if (balanceFactor > 1) {
            if (getBalance(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        // Right Heavy
        if (balanceFactor < -1) {
            if (getBalance(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    int getBalance(Node* node) { return node ? height(node->left) - height(node->right) : 0; }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* insert(Node* node, const K& key, const V& value) {
        if (!node) return new Node(key, value);
        if (key < node->key) node->left = insert(node->left, key, value);
        else if (key > node->key) node->right = insert(node->right, key, value);
        else return node;

        updateHeight(node);
        return balance(node);
    }

    Node* remove(Node* node, const K& key) {
        if (!node) return nullptr;
        if (key < node->key) node->left = remove(node->left, key);
        else if (key > node->key) node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            Node* successor = getMinValueNode(node->right);
            node->key = successor->key;
            node->value = successor->value;
            node->right = remove(node->right, successor->key);
        }

        updateHeight(node);
        return balance(node);
    }

    Node* search(Node* node, const K& key) const {
        if (!node || node->key == key) return node;
        return key < node->key ? search(node->left, key) : search(node->right, key);
    }

    Node* getMinValueNode(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void updateHeight(Node* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() { clear(root); }

    void insert(const K& key, const V& value) { root = insert(root, key, value); }

    void remove(const K& key) { root = remove(root, key); }

    bool contains(const K& key) const { return search(root, key) != nullptr; }

    /**
    * Returns the number of nodes in the AVLTree.
    */
    int getSize() const {
        return countNodes(root);
    }

    /**
     * Helper function to count nodes.
     */
    int countNodes(Node* node) const {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    V& get(const K& key) {
        Node* node = search(root, key);
        if (!node) throw std::invalid_argument("Key not found");
        return node->value;
    }

    const V& get(const K& key) const {  // Const version
        Node* node = search(root, key);
        if (!node) throw std::invalid_argument("Key not found");
        return node->value;
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

    /**
     * In-order iterator for AVLTree using a List-based stack.
     */
    class AVLTreeIterator : public Iterator<std::pair<K, V>> {
    private:
        List<Node*> nodeStack;

        void pushLeft(Node* node) {
            while (node) {
                nodeStack.add(node);
                node = node->left;
            }
        }

    public:
        explicit AVLTreeIterator(Node* root) { pushLeft(root); }

        bool hasNext() const override { return !nodeStack.isEmpty(); }

        std::pair<K, V> next() override {
            if (!hasNext()) throw std::out_of_range("No more elements in AVLTree");

            Node* node = nodeStack.getHead()->data;
            nodeStack.remove(node);

            pushLeft(node->right);

            return { node->key, node->value };
        }
    };

    Iterator<std::pair<K, V>>* createIterator() const {
        return new AVLTreeIterator(root);
    }
};
