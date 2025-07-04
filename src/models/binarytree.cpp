#include "binarytree.h"

BinaryTree::BinaryTree(int root)
    : m_root(new TreeNode(root))
{

}

BinaryTree::~BinaryTree()
{

}

bool BinaryTree::insert(int value)
{
    if (!m_root) {
        m_root = new TreeNode(value);
        return true;
    }

    TreeNode* current = m_root;
    while (true) {
        if (value == current->value) {
            return false;
        }

        if (value < current->value) {
            if (!current->left) {
                current->left = new TreeNode(value);
                return true;
            }
            current = current->left;
        } else {
            if (!current->right) {
                current->right = new TreeNode(value);
                return true;
            }
            current = current->right;
        }
    }
}

bool BinaryTree::remove(int value)
{
    bool isFound = false;
    m_root = removeRecursive(m_root, value, isFound);
    return isFound;
}

TreeNode *BinaryTree::insertRecursive(TreeNode *node, int value)
{
    if (!node)
        return new TreeNode(value);

    if (value < node->value) {
        node->left = insertRecursive(node->left, value);
    } else if (value > node->value) {
        node->right = insertRecursive(node->right, value);
    }

    return node;
}

TreeNode *BinaryTree::removeRecursive(TreeNode *node, int value, bool &isFound)
{
    if (!node)
        return nullptr;

    if (value < node->value) {
        node->left = removeRecursive(node->left, value, isFound);
    } else if (value > node->value) {
        node->right = removeRecursive(node->right, value, isFound);
    } else {
        isFound = true;
        if (!node->left) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }

        TreeNode* minRight = findMin(node->right);
        node->value = minRight->value;
        node->right = removeRecursive(node->right, minRight->value, isFound);
    }

    return node;
}

TreeNode *BinaryTree::findMin(TreeNode *node)
{
    if (!node)
        return nullptr;

    while (node->left)
        node = node->left;

    return node;
}

TreeNode *BinaryTree::findNode(TreeNode *node, int value)
{
    if (!node)
        return nullptr;

    if (node->value == value)
        return node;

    if (value < node->value) {
        return findNode(node->left, value);
    } else if (value > node->value) {
        return findNode(node->right, value);
    }

    return node;
}

std::pair<TreeNode *, TreeNode *> BinaryTree::findNodeAndParent(TreeNode *node, TreeNode *parent, int value)
{
    if (!node)
        return {nullptr, nullptr};

    if (node->value == value)
        return {node, parent};

    if (value < node->value) {
        return findNodeAndParent(node->left, node, value);
    } else if (value > node->value) {
        return findNodeAndParent(node->right, node, value);
    }

    return {node, parent};
}
