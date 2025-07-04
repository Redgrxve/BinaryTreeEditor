#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "customgraphicsview.h"
#include "binarytree.h"

class TreeScene;

class TreeView : public CustomGraphicsView
{
public:
    explicit TreeView(QWidget *parent = nullptr);

    void setTree(const BinaryTree &tree) { m_tree = tree; }
    void drawTree();

private:
    TreeScene *m_scene;
    BinaryTree m_tree;
};

#endif // TREEVIEW_H
