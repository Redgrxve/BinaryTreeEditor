#ifndef BINARYTREE_H
#define BINARYTREE_H

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
    BinaryTree(int root);
    ~BinaryTree();

    inline TreeNode *root() const { return m_root; }

    bool insert(int value);
    bool remove(int value);

    int depth() const;

private:
    TreeNode *m_root = nullptr;

    TreeNode *insertRecursive(TreeNode *node, int value);
    TreeNode *removeRecursive(TreeNode *node, int value, bool &isFound);

    TreeNode *findMin(TreeNode *parent) const;
    TreeNode *findNode(TreeNode *current, int value) const;
    std::pair<TreeNode *, TreeNode *> findNodeAndParent(TreeNode *current, TreeNode *parent, int value) const;

    int getDepthRecursive(TreeNode* node) const;
};

#endif // BINARYTREE_H
