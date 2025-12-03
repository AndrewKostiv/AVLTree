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

/**
 * printRecursive
 * @return void
 */

void AVLTree::printTree() const
{
    if (!root)
    {
        std::cout << "no root" << std::endl;
    }

    printRecursive(this->root);
}
/**
 * printRecursive
 * @param const AVLNode *currentNode
 * @return void
 */
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

/**
 * removeNode
 * @param int key
 * @return bool
 */
bool AVLTree::remove(int key)
{
    AVLNode *node = search(key);
    AVLNode *parent = getParent(node);
    return removeNode(parent, node);
}
/**
 * removeNode
 * @param AVLNode* parent
 * @param AVLNode* node
 * @return bool
 */
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

/**
 * getRoot
 * @return AVLNode*
 */
AVLNode *AVLTree::getRoot() const
{
    return this->root;
}

/**
 * search
 * @param int key
 */

AVLNode *AVLTree::search(int key) const
{
    return searchRecursive(root, key);
}

/**
 * searchRecursive
 * @param AVLNode* node
 * @param int key
 */
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
/**
 * getParent
 * @param AVLNode* node
 */
AVLNode *AVLTree::getParent(AVLNode *node) const
{
    return getParentRecursive(root, node);
}
/**
 * getParentRecursive
 * @param AVLNode* subtreeRoot
 * @param const AVLNode* node
 */
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

/**
 * AVLTreeUpdateHeight
 * @param AVLNode* node
 */
void AVLTree::AVLTreeUpdateHeight(AVLNode *node)
{
    int leftHeight = -1;
    if (node->left != nullptr)
        leftHeight = node->left->height;
    int rightHeight = -1;
    if (node->right != nullptr)
        rightHeight = node->right->height;
    node->height = std::max(leftHeight, rightHeight) + 1;
}

/**
 * AVLTreeSetChild
 * @param AVLNode* parent
 * @param const std::string &whichChild
 * @param AVLNode* child
 */
bool AVLTree::AVLTreeSetChild(AVLNode *parent, const std::string &whichChild, AVLNode *child)
{
    if (whichChild != "left" && whichChild != "right")
        return false;

    if (whichChild == "left")
        parent->left = child;
    else
        parent->right = child;
    if (child != nullptr)
        child->parent = parent;

    AVLTreeUpdateHeight(parent);
    return true;
}
/**
 * AVLTreeReplaceChild
 * @param AVLNode* parent
 * @param AVLNode* currentChild
 * @param AVLNode* newChild
 */
bool AVLTree::AVLTreeReplaceChild(AVLNode *parent, AVLNode *currentChild, AVLNode *newChild)
{
    if (parent->left == currentChild)
        return AVLTreeSetChild(parent, "left", newChild);
    else if (parent->right == currentChild)
        return AVLTreeSetChild(parent, "right", newChild);
    return false;
}
/**
 * AVLTreeGetBalance
 * @param AVLNode* node
 */
int AVLTree::AVLTreeGetBalance(AVLNode *node)
{
    int leftHeight = -1;
    if (node->left != nullptr)
        leftHeight = node->left->height;
    int rightHeight = -1;
    if (node->right != nullptr)
        rightHeight = node->right->height;
    return leftHeight - rightHeight;
}

/**
 * AVLTreeRotateRight
 * @param AVLTree* tree
 * @param AVLNode* node
 */

AVLNode *AVLTree::AVLTreeRotateRight(AVLTree *tree, AVLNode *node)
{
    AVLNode *leftRightChild = node->left->right;
    if (node->parent != nullptr)
        AVLTreeReplaceChild(node->parent, node, node->left);
    else
    { // node is root
        tree->root = node->left;
        tree->root->parent = nullptr;
    }
    AVLTreeSetChild(node->left, "right", node);
    AVLTreeSetChild(node, "left", leftRightChild);
    return node->left;
}
/**
 * AVLTreeRotateLeft
 * @param AVLTree* tree
 * @param AVLNode* node
 */
AVLNode *AVLTree::AVLTreeRotateLeft(AVLTree *tree, AVLNode *node)
{
    AVLNode *rightLeftChild = node->right->left;
    if (node->parent != nullptr)
        AVLTreeReplaceChild(node->parent, node, node->right);
    else
    { // node is root
        tree->root = node->right;
        tree->root->parent = nullptr;
    }
    AVLTreeSetChild(node->right, "left", node);
    AVLTreeSetChild(node, "right", rightLeftChild);
    return node->right;
}

/**
 * AVLTreeRebalance
 * @param AVLTree* tree
 * @param AVLNode* node
 */
AVLNode *AVLTree::AVLTreeRebalance(AVLTree *tree, AVLNode *node)
{
    AVLTreeUpdateHeight(node);
    if (AVLTreeGetBalance(node) == -2)
    {
        if (AVLTreeGetBalance(node->right) == 1)
        {
            // Double rotation case.
            AVLTreeRotateRight(tree, node->right);
        }
        return AVLTreeRotateLeft(tree, node);
    }
    else if (AVLTreeGetBalance(node) == 2)
    {
        if (AVLTreeGetBalance(node->left) == -1)
        {
            // Double rotation case.
            AVLTreeRotateLeft(tree, node->left);
        }
        return AVLTreeRotateRight(tree, node);
    }
    return node;
}
/**
 * AVLTreeInsertKey
 * @param AVLTree* tree
 * @param int data
 */
bool AVLTree::AVLTreeInsertKey(AVLTree *tree, int data)
{
    if (search(data))
        return false;

    AVLNode *newNode = new AVLNode(data);
    AVLTreeInsertNode(tree, newNode);
    return true;
}

void AVLTree::AVLTreeInsertNode(AVLTree *tree, AVLNode *node)
{
    if (tree->root == nullptr)
    {
        tree->root = node;
        node->parent = nullptr;
        return;
    }

    AVLNode *cur = tree->root;
    while (cur != nullptr)
    {
        if (node->data < cur->data)
        {
            if (cur->left == nullptr)
            {
                cur->left = node;
                node->parent = cur;
                cur = nullptr;
            }
            else
            {
                cur = cur->left;
            }
        }
        else
        {
            if (cur->right == nullptr)
            {
                cur->right = node;
                node->parent = cur;
                cur = nullptr;
            }
            else
                cur = cur->right;
        }
    }

    node = node->parent;
    while (node != nullptr)
    {
        AVLTreeRebalance(tree, node);
        node = node->parent;
    }
}
/**
 * AVLTreeRemoveNode
 * @param AVLTree* tree
 * @param AVLNode* node
 */
bool AVLTree::AVLTreeRemoveNode(AVLTree *tree, AVLNode *node)
{
    if (node == nullptr)
    {
        return false;
    }

    // Parent needed for rebalancing
    AVLNode *parent = node->parent;

    // Case 1: Internal node with 2 children
    if (node->left != nullptr && node->right != nullptr)
    {
        // Find successor
        AVLNode *succNode = node->right;
        while (succNode->left != nullptr)
        {
            succNode = succNode->left;
        }

        // Copy the key from the successor node
        node->data = succNode->data;

        // Recursively remove successor
        AVLTreeRemoveNode(tree, succNode);

        // Nothing left to do since the recursive call will have rebalanced
        return true;
    }

    // Case 2: Root node (with 1 or 0 children)
    else if (node == tree->root)
    {
        if (node->left != nullptr)
        {
            tree->root = node->left;
        }
        else
        {
            tree->root = node->right;
        }
        if (tree->root != nullptr)
        {
            tree->root->parent = nullptr;
        }
        return true;
    }

    // Case 3: Internal with left child only
    else if (node->left != nullptr)
    {
        AVLTreeReplaceChild(parent, node, node->left);
    }
    // Case 4: Internal with right child only OR leaf
    else
    {
        AVLTreeReplaceChild(parent, node, node->right);
    }

    // node is gone. Anything that was below node that has persisted is already correctly
    // balanced, but ancestors of node may need rebalancing.
    node = parent;
    while (node != nullptr)
    {
        AVLTreeRebalance(tree, node);
        node = node->parent;
    }
    return true;
}