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
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    // Left rotation
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    // Insert a node
    Node* insert(Node* node, const K& key, const V& value) {
        if (!node) return new Node(key, value);

        if (key < node->key) node->left = insert(node->left, key, value);
        else if (key > node->key) node->right = insert(node->right, key, value);
        else return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);
        if (balance > 1 && key < node->left->key) return rotateRight(node);
        if (balance < -1 && key > node->right->key) return rotateLeft(node);
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    // Search for a key
    Node* search(Node* node, const K& key) const {
        if (!node || node->key == key) return node;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

public:
    AVLTree() : root(nullptr) {}

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

