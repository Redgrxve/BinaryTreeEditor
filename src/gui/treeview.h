#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "customgraphicsview.h"
#include "binarytree.h"

class TreeScene;

class TreeView : public CustomGraphicsView
{
public:
    explicit TreeView(QWidget *parent = nullptr);

    void setTree(BinaryTree *tree);
    void updateScene();
    void deleteSelectedNodes();

private:
    TreeScene *treeScene() const;
};

#endif // TREEVIEW_H
