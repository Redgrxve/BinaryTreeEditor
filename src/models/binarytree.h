#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <functional>
#include <qcontainerfwd.h>
#include <utility>

struct TreeNode {
    TreeNode(int val) : value(val) {}

    int value;
    TreeNode *left  = nullptr;
    TreeNode *right = nullptr;
};

class BinaryTree
{ 
public:
    BinaryTree() = default;
    BinaryTree(TreeNode *root);
    BinaryTree(int root);
    BinaryTree(const BinaryTree &other);
    BinaryTree(BinaryTree &&other);
    ~BinaryTree();

    inline TreeNode *root() const { return m_root; }

    bool insert(int value);
    bool remove(int value);

    int depth() const;

    void clear();
    void levelOrder(std::function<void(TreeNode *)> handle);

    QVector<QVector<TreeNode *>> levelOrderNodes() const;

    BinaryTree &operator=(const BinaryTree &other);
    BinaryTree &operator=(BinaryTree &&other);

private:
    TreeNode *m_root{};

    TreeNode *insertRecursive(TreeNode *node, int value);
    TreeNode *removeRecursive(TreeNode *node, int value, bool &isFound);

    void clearRecursive(TreeNode *node);

    TreeNode *copyTree(const TreeNode *node);

    TreeNode *findMin(TreeNode *parent) const;
    TreeNode *findNode(TreeNode *current, int value) const;
    std::pair<TreeNode *, TreeNode *> findNodeAndParent(TreeNode *current, TreeNode *parent, int value) const;

    int getDepthRecursive(TreeNode* node) const;
};

#endif // BINARYTREE_H
