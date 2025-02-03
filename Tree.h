#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Tree {
private:
    struct Node {
        T data;
        Node* left, * right;
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void addHelper(Node*& node, const T& value) {
        if (!node) node = new Node(value);
        else if (value < node->data) addHelper(node->left, value);
        else addHelper(node->right, value);
    }

public:
    Tree() : root(nullptr) {}

    void add(const T& value) { addHelper(root, value); }

    bool contains(const T& value) const {
        Node* current = root;
        while (current) {
            if (current->data == value) return true;
            current = (value < current->data) ? current->left : current->right;
        }
        return false;
    }
};

