#include "binarytree.h"

#include <QQueue>
#include <qminmax.h>

BinaryTree::BinaryTree(TreeNode *root)
    : m_root(root) {}

BinaryTree::BinaryTree(int root)
    : m_root(new TreeNode(root)) {}

BinaryTree::BinaryTree(const BinaryTree &other)
{
    clear();
    m_root = copyTree(other.m_root);
}

BinaryTree::BinaryTree(BinaryTree &&other)
{
    clear();

    m_root = other.m_root;
    other.m_root = nullptr;
}

BinaryTree::~BinaryTree()
{
    clear();
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

int BinaryTree::depth() const
{
    return getDepthRecursive(m_root);
}

void BinaryTree::clear()
{
    clearRecursive(m_root);
    m_root = nullptr;
}

void BinaryTree::levelOrder(std::function<void(TreeNode *)> handle)
{
    if (!m_root) return;

    QQueue<TreeNode *> q;
    q.enqueue(m_root);

    while (!q.empty()) {
        auto node = q.dequeue();
        handle(node);
        if (node->left)
            q.enqueue(node->left);
        if (node->right)
            q.enqueue(node->right);
    }
}

QVector<QVector<TreeNode *>> BinaryTree::levelOrderNodes() const
{
    QVector<QVector<TreeNode*>> result{};
    if (!m_root) return result;

    QQueue<TreeNode*> q;
    q.enqueue(m_root);

    while (!q.empty()) {
        const size_t levelSize = q.size();
        QVector<TreeNode*> currentLevel;
        currentLevel.reserve(levelSize);

        for (size_t i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.dequeue();
            currentLevel.push_back(node);

            if (node->left)
                q.enqueue(node->left);
            if (node->right)
                q.enqueue(node->right);
        }

        result.push_back(std::move(currentLevel));
    }

    return result;
}

BinaryTree &BinaryTree::operator=(const BinaryTree &other)
{
    if (this == &other) return *this;

    clear();
    m_root = copyTree(other.m_root);
    return *this;
}

BinaryTree &BinaryTree::operator=(BinaryTree &&other)
{
    if (this == &other) return *this;

    clear();
    m_root = other.m_root;
    other.m_root = nullptr;
    return *this;
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

void BinaryTree::clearRecursive(TreeNode *node)
{
    if (!node) return;

    clearRecursive(node->left);
    clearRecursive(node->right);
    delete node;
}

TreeNode *BinaryTree::copyTree(const TreeNode *node)
{
    if (!node) return nullptr;

    auto newNode = new TreeNode(node->value);
    newNode->left  = copyTree(node->left);
    newNode->right = copyTree(node->right);

    return newNode;
}

TreeNode *BinaryTree::findMin(TreeNode *node) const
{
    if (!node)
        return nullptr;

    while (node->left)
        node = node->left;

    return node;
}

TreeNode *BinaryTree::findNode(TreeNode *node, int value) const
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

std::pair<TreeNode *, TreeNode *> BinaryTree::findNodeAndParent(TreeNode *node, TreeNode *parent, int value) const
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

int BinaryTree::getDepthRecursive(TreeNode *node) const
{
    if (!node) return 0;

    return 1 + qMax(getDepthRecursive(node->left), getDepthRecursive(node->right));
}
