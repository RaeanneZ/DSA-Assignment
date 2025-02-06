#pragma once
#include "Iterator.h"
#include <stdexcept>

using namespace std;

/**
 * Template class for an AVL Tree
 * Supports insertion, searching, deletion, and iteration.
 */
template <typename K, typename V>
class AVLTree
{
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

    // Copy helper
    Node* copy(Node* node) {
        if (!node) return nullptr;
        Node* newNode = new Node(node->key, node->value);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

    // Get height of a node
    int height(Node* node) {
        return node ? node->height : 0;
    }

    // Get balance factor of a node
    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    // Right rotation
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    // Left rotation
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // Insert node
    Node* insert(Node* node, const K& key, const V& value) {
        if (!node) return new Node(key, value);
        if (key < node->key) node->left = insert(node->left, key, value);
        else if (key > node->key) node->right = insert(node->right, key, value);
        else return node;

        updateHeight(node);
        return balance(node);
    }

    // Balance the tree
    Node* balance(Node* node) {
        int balanceFactor = getBalance(node);
        if (balanceFactor > 1 && getBalance(node->left) >= 0) return rotateRight(node);
        if (balanceFactor < -1 && getBalance(node->right) <= 0) return rotateLeft(node);
        if (balanceFactor > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balanceFactor < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    // Search for a key
    Node* search(Node* node, const K& key) const {
        if (!node || node->key == key) return node;
        return key < node->key ? search(node->left, key) : search(node->right, key);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void updateHeight(Node* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }

public:
    AVLTree() : root(nullptr) {}

    // Deep copy constructor
    AVLTree(const AVLTree& other) { root = copy(other.root); }

    ~AVLTree() { clear(root); }

    void insert(const K& key, const V& value) {
        root = insert(root, key, value);
    }

    V& get(const K& key) {
        Node* node = search(root, key);
        if (!node) throw invalid_argument("Key not found");
        return node->value;
    }

    bool contains(const K& key) const {
        return search(root, key) != nullptr;
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    class AVLTreeIterator : public Iterator<pair<K, V>> {
    private:
        struct StackNode {
            Node* node;
            StackNode* next;
        };
        StackNode* stackTop;

        void pushLeft(Node* node) {
            while (node) {
                stackTop = new StackNode{ node, stackTop };
                node = node->left;
            }
        }

    public:
        explicit AVLTreeIterator(Node* root) : stackTop(nullptr) {
            pushLeft(root);
        }

        ~AVLTreeIterator() {
            while (stackTop) {
                StackNode* temp = stackTop;
                stackTop = stackTop->next;
                delete temp;
            }
        }

        bool hasNext() const override {
            return stackTop != nullptr;
        }

        pair<K, V> next() override {
            if (!hasNext()) throw out_of_range("No more elements");

            Node* node = stackTop->node;
            stackTop = stackTop->next;
            pushLeft(node->right);
            return { node->key, node->value };
        }
    };

    Iterator<pair<K, V>>* createIterator() const {
        return new AVLTreeIterator(root);
    }
};

