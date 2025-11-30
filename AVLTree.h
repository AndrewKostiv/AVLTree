#pragma once
#include <iostream>
struct AVLNode
{
    int data;
    int balanceFactor;
    AVLNode *left = nullptr;
    AVLNode *right = nullptr;
    AVLNode() {};
    AVLNode(int data)
    {
        this->data = data;
    };
    int getBalanceFactor()
    {
        int leftHeight = !left ? -1 : left->getBalanceFactor();
        int rightHeight = !right ? -1 : right->getBalanceFactor();
        return leftHeight - rightHeight;
    }
};

class BSTree
{
private:
    AVLNode *root = nullptr;

    bool insertNode(AVLNode *current, AVLNode *newNode);
    bool removeNode(AVLNode *parent, AVLNode *node);
    void printRecursive(const AVLNode *thisNode) const;
    AVLNode *searchRecursive(AVLNode *node, int key) const;
    AVLNode *getParentRecursive(AVLNode *subtreeRoot, const AVLNode *node) const;

public:
    BSTree(/* args */);
    ~BSTree();
    bool insert(int data);
    bool remove(int data);
    bool deleteNode(AVLNode &thisNode);
    void printTree() const;
    AVLNode *search(int key) const;
    AVLNode *getRoot() const;
    AVLNode *getParent(AVLNode *node) const;
};
