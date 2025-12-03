#pragma once
#include <iostream>
struct AVLNode
{
    int data;
    int balanceFactor;
    int height;
    AVLNode *left = nullptr;
    AVLNode *right = nullptr;
    AVLNode *parent = nullptr;
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

class AVLTree
{
private:
    bool insertNode(AVLNode *current, AVLNode *newNode);
    bool removeNode(AVLNode *parent, AVLNode *node);
    void printRecursive(const AVLNode *thisNode) const;
    AVLNode *searchRecursive(AVLNode *node, int key) const;
    AVLNode *getParentRecursive(AVLNode *subtreeRoot, const AVLNode *node) const;

public:
    AVLNode *root = nullptr;
    AVLTree(/* args */);
    ~AVLTree();
    bool insert(int data);
    bool remove(int data);
    bool deleteNode(AVLNode &thisNode);
    void printTree() const;
    AVLNode *search(int key) const;
    AVLNode *getRoot() const;
    AVLNode *getParent(AVLNode *node) const;
    void AVLTreeUpdateHeight(AVLNode *node);
    int AVLTreeGetBalance(AVLNode *node);
    bool AVLTreeReplaceChild(AVLNode *parent, AVLNode *currentChild, AVLNode *newChild);
    bool AVLTreeSetChild(AVLNode *parent, const std::string &whichChild, AVLNode *child);
    AVLNode *AVLTreeRotateRight(AVLTree *tree, AVLNode *node);
    AVLNode *AVLTreeRotateLeft(AVLTree *tree, AVLNode *node);
    AVLNode *AVLTreeRebalance(AVLTree *tree, AVLNode *node);
    bool AVLTreeInsertKey(AVLTree *tree, int key);
    void AVLTreeInsertNode(AVLTree *tree, AVLNode *node);
    bool AVLTreeRemoveKey(AVLTree *tree, int key);
    bool AVLTreeRemoveNode(AVLTree *tree, AVLNode *node);
};
