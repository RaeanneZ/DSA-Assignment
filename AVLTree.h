/*
* Member 1 Name: Zou Ruining, Raeanne
* Member 1 ID: S10258772G
* Member 2 Name: Cing Sian Kim
* Member 2 ID: S10257716F
* Group: 1
*/


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

    /**
    * Retrieves the height of a node.
    * Process: Returns the height of the given node or `0` if the node is null.
    * Precondition: `node` must be a valid pointer or `nullptr`.
    * Postcondition: Returns the height of the node.
    */
    int height(Node* node) { return node ? node->height : 0; }


    /**
    * Balances the AVL Tree at a given node.
    * Process: Calculates the balance factor and performs rotations if necessary.
    * Precondition: `node` must be a valid AVL Tree node.
    * Postcondition: The tree remains balanced after insertion or deletion.
    */
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


    /**
    * Computes the balance factor of a node.
    * Process: Returns the difference between the height of the left and right subtrees.
    * Precondition: `node` must be a valid AVL Tree node.
    * Postcondition: Returns the balance factor of the node.
    */
    int getBalance(Node* node) { return node ? height(node->left) - height(node->right) : 0; }


    /**
    * Performs a right rotation on the given node.
    * Process: Rebalances the tree by moving the left child up and the node down.
    * Precondition: `y` must have a left child.
    * Postcondition: The subtree is rotated to the right, restoring AVL balance.
    */
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }


    /**
    * Performs a left rotation on the given node.
    * Process: Rebalances the tree by moving the right child up and the node down.
    * Precondition: `x` must have a right child.
    * Postcondition: The subtree is rotated to the left, restoring AVL balance.
    */
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


    /**
    * Searches for a key in the AVL Tree.
    * Process: Uses recursive traversal to locate the key.
    * Precondition: `key` must be a valid key type.
    * Postcondition: Returns a pointer to the node containing the key, or `nullptr` if not found.
    */
    Node* search(Node* node, const K& key) const {
        if (!node || node->key == key) return node;
        return key < node->key ? search(node->left, key) : search(node->right, key);
    }


    /**
    * Finds the node with the smallest key in the tree.
    * Process: Traverses the left subtree to locate the smallest node.
    * Precondition: `node` must not be `nullptr`.
    * Postcondition: Returns a pointer to the node with the smallest key.
    */
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


    /**
    * Updates the height of a node based on its children's heights.
    * Process: Sets the height of the node to 1 plus the maximum height of its children.
    * Precondition: `node` must be a valid AVL Tree node.
    * Postcondition: The node's height is updated.
    */
    void updateHeight(Node* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }

public:
    /**
    * Constructor
    * Process: Initializes an empty AVL Tree.
    * Precondition: None.
    * Postcondition: An empty AVL Tree object is created with a `nullptr` root.
    */
    AVLTree() : root(nullptr) {}


    /**
    * Destructor
    * Process: Calls `clear()` to free dynamically allocated memory for all nodes.
    * Precondition: None.
    * Postcondition: All nodes in the tree are deleted, and memory is freed.
    */
    ~AVLTree() { clear(root); }


    /**
    * Inserts a key-value pair into the AVL Tree.
    * Process: Uses a recursive approach to insert the key-value pair while maintaining AVL balancing.
    * Precondition: `key` must be unique within the tree.
    * Postcondition: The key-value pair is inserted, and the tree is rebalanced if necessary.
    */
    void insert(const K& key, const V& value) { root = insert(root, key, value); }


    /**
    * Removes a key from the AVL Tree.
    * Process: Searches for the key, removes it if found, and rebalances the tree.
    * Precondition: The key must exist in the tree; otherwise, the function does nothing.
    * Postcondition: The key is removed from the tree, and rebalancing is performed.
    */
    void remove(const K& key) { root = remove(root, key); }


    /**
    * Checks if a key exists in the AVL Tree.
    * Process: Uses a recursive search to determine if the key is present.
    * Precondition: `key` must be a valid key type.
    * Postcondition: Returns `true` if the key exists, otherwise returns `false`.
    */
    bool contains(const K& key) const { return search(root, key) != nullptr; }

    /**
    * Returns the number of nodes in the AVL Tree.
    * Process: Calls a recursive helper function to count nodes.
    * Precondition: None.
    * Postcondition: Returns the total number of nodes in the tree.
    */
    int getSize() const {
        return countNodes(root);
    }


    /**
    * Helper function to count the number of nodes in the tree.
    * Process: Recursively traverses the tree and counts all nodes.
    * Precondition: `node` must be a valid AVL Tree node or `nullptr`.
    * Postcondition: Returns the total number of nodes in the subtree.
    */
    int countNodes(Node* node) const {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }


    /**
    * Retrieves the value associated with a key.
    * Process: Uses a recursive search to find the key and return its associated value.
    * Precondition: The key must exist in the tree; otherwise, an exception is thrown.
    * Postcondition: Returns a reference to the value associated with the key.
    */
    V& get(const K& key) {
        Node* node = search(root, key);
        if (!node) throw invalid_argument("Key not found");
        return node->value;
    }


    /**
    * Retrieves the value associated with a key (const version).
    * Process: Uses a recursive search to find the key and return its associated value.
    * Precondition: The key must exist in the tree; otherwise, an exception is thrown.
    * Postcondition: Returns a constant reference to the value associated with the key.
    */
    const V& get(const K& key) const {  // Const version
        Node* node = search(root, key);
        if (!node) throw invalid_argument("Key not found");
        return node->value;
    }


    /**
    * Clears all nodes from the AVL Tree.
    * Process: Calls a recursive helper function to delete all nodes and sets the root to `nullptr`.
    * Precondition: None.
    * Postcondition: The tree is emptied, and all dynamically allocated memory is freed.
    */
    void clear() {
        clear(root);
        root = nullptr;
    }


    /**
    * Iterator for in-order traversal of the AVL Tree.
    * Process: Uses a stack to traverse the tree in in-order fashion.
    * Precondition: `root` must be a valid AVL Tree node or `nullptr`.
    * Postcondition: Allows iteration over key-value pairs in sorted order.
    */
    class AVLTreeIterator : public Iterator<pair<K, V>> {
    private:
        List<Node*> nodeStack;

        /**
        * Pushes all left children of a node onto the stack.
        * Process: Iterates down the left subtree, pushing each node onto the stack.
        * Precondition: `node` must be a valid pointer or `nullptr`.
        * Postcondition: All left descendants of `node` are added to `nodeStack`.
        */
        void pushLeft(Node* node) {
            while (node) {
                nodeStack.add(node);
                node = node->left;
            }
        }

    public:
        /**
        * Constructor for AVLTreeIterator.
        * Process: Initializes the iterator by pushing all left nodes of the tree onto the stack.
        * Precondition: `root` must be a valid pointer to the root node of an AVL Tree or `nullptr`.
        * Postcondition: The iterator is initialized with the leftmost path of the tree.
        */
        explicit AVLTreeIterator(Node* root) { pushLeft(root); }


        /**
        * Checks if there are more elements to iterate over in the AVL Tree.
        * Process: Returns `true` if the stack is not empty, indicating that more elements exist.
        * Precondition: None.
        * Postcondition: Returns `true` if there are more elements, otherwise returns `false`.
        */
        bool hasNext() const override { return !nodeStack.isEmpty(); }


        /**
        * Retrieves the next key-value pair in in-order traversal.
        * Process: Pops the next node from the stack, processes its key-value pair, and pushes its right subtree.
        * Precondition: `hasNext()` must return `true`; otherwise, an exception is thrown.
        * Postcondition: Returns the next key-value pair in sorted order.
        */
        pair<K, V> next() override {
            if (!hasNext()) throw out_of_range("No more elements in AVLTree");

            Node* node = nodeStack.getHead()->data;
            nodeStack.remove(node);

            pushLeft(node->right);

            return { node->key, node->value };
        }
    };


    /**
    * Creates an iterator for in-order traversal of the AVL Tree.
    * Process: Instantiates an `AVLTreeIterator` object with the root node.
    * Precondition: None.
    * Postcondition: Returns an iterator for in-order traversal of the tree.
    */
    Iterator<pair<K, V>>* createIterator() const {
        return new AVLTreeIterator(root);
    }
};
