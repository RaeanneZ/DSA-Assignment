#pragma once
#include "Tree.h"

template <typename T>
class AVLTree : public Tree<T> {
private:
    int height(TreeNode* node) { return node ? node->height : 0; }

    int getBalance(TreeNode* node) { return node ? height(node->left) - height(node->right) : 0; }

    TreeNode* rotateRight(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        return x;
    }

    TreeNode* rotateLeft(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        return y;
    }

public:
    void add(const T& value) {
        this->root = addAVL(this->root, value);
    }

    TreeNode* addAVL(TreeNode* node, const T& value) {
        if (!node) return new TreeNode(value);
        if (value < node->data) node->left = addAVL(node->left, value);
        else node->right = addAVL(node->right, value);

        int balance = getBalance(node);
        if (balance > 1 && value < node->left->data) return rotateRight(node);
        if (balance < -1 && value > node->right->data) return rotateLeft(node);
        return node;
    }
};
