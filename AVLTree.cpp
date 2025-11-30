#include "AVLTree.h"

// =============================

// Constructor & Destructor

// =============================

AVLTree::AVLTree()
{
    AVLNode *root = nullptr;
}

AVLTree::~AVLTree() {}

// =============================

// insert

// =============================
bool AVLTree::insert(int data)
{
    AVLNode *node = new AVLNode(data);
    if (!root)
    {
        root = node;
        return true;
    }
    else
    {
        return insertNode(root, node);
    }
    return false;
}

bool AVLTree::insertNode(AVLNode *parent, AVLNode *nodeToInsert)
{
    if (nodeToInsert->data < parent->data)
    {
        if (!parent->left)
        {
            parent->left = nodeToInsert;
            return true;
        }
        else
            return insertNode(parent->left, nodeToInsert);
    }
    else
    {
        if (!parent->right)
        {
            parent->right = nodeToInsert;
            return true;
        }
        else
            return insertNode(parent->right, nodeToInsert);
    }
    return false;
}

// =============================

// print

// =============================

void AVLTree::printTree() const
{
    if (!root)
    {
        std::cout << "no root" << std::endl;
    }

    printRecursive(this->root);
}

void AVLTree::printRecursive(const AVLNode *currentNode) const
{
    if (currentNode == nullptr)
    {
        return;
    }
    std::cout << currentNode->data << std::endl;
    printRecursive(currentNode->left);
    printRecursive(currentNode->right);
}

// =============================

// Remove

// =============================
bool AVLTree::remove(int key)
{
    AVLNode *node = search(key);
    AVLNode *parent = getParent(node);
    return removeNode(parent, node);
}

bool AVLTree::removeNode(AVLNode *parent, AVLNode *node)

{
    if (node == nullptr)
    {
        return false;
    }

    // Case 1: Internal node with 2 children
    if (node->left && node->right)
    {
        // Find successor and successor's parent
        AVLNode *successorNode = node->right;
        AVLNode *successorParent = node;
        while (successorNode->left)
        {
            successorParent = successorNode;
            successorNode = successorNode->left;
        }

        // Copy the key from the successor node
        node->data = successorNode->data;

        // Recursively remove successor node
        removeNode(successorParent, successorNode);
    }

    // Case 2: Root node (with 1 or 0 children)
    else if (node == root)
    {
        if (node->left)
        {
            root = node->left;
        }
        else
        {
            root = node->right;
        }
    }

    // Case 3: Internal with left child only
    else if (node->left)
    {
        // Replace node with node's left child
        if (parent->left == node)
        {
            parent->left = node->left;
        }
        else
        {
            parent->right = node->left;
        }
    }

    // Case 4: Internal with right child only OR leaf
    else
    {
        // Replace node with node's right child
        if (parent->left == node)
        {
            parent->left = node->right;
        }
        else
        {
            parent->right = node->right;
        }
    }

    return true;
}

// =============================

// Getters & Setters

// =============================
AVLNode *AVLTree::getRoot() const
{
    return this->root;
}

// =============================

// Search

// =============================

AVLNode *AVLTree::search(int key) const
{
    return searchRecursive(root, key);
}

AVLNode *AVLTree::searchRecursive(AVLNode *node, int key) const
{
    if (node)
    {
        if (key == node->data)
        {
            return node;
        }
        else if (key < node->data)
        {
            return searchRecursive(node->left, key);
        }
        else
        {
            return searchRecursive(node->right, key);
        }
    }
    return nullptr;
}
// =============================

// getParent

// =============================
AVLNode *AVLTree::getParent(AVLNode *node) const
{
    return getParentRecursive(root, node);
}

AVLNode *AVLTree::getParentRecursive(AVLNode *subtreeRoot, const AVLNode *node) const
{
    if (subtreeRoot == nullptr)
        return nullptr;

    if (subtreeRoot->left == node ||
        subtreeRoot->right == node)
    {
        return subtreeRoot;
    }

    if (node->data < subtreeRoot->data)
    {
        return getParentRecursive(subtreeRoot->left, node);
    }
    return getParentRecursive(subtreeRoot->right, node);
}
