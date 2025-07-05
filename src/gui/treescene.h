#ifndef TREESCENE_H
#define TREESCENE_H

#include "binarytree.h"
#include <QGraphicsScene>

class TreeScene : public QGraphicsScene
{
public:
    explicit TreeScene(QObject *parent = nullptr);

    void setTree(BinaryTree *tree);

    void redraw();
    void draw();

    void deleteSelectedNodes();

private:
    void drawTree(TreeNode *root, int maxDepth, int x = 0, int y = 0, int depth = 0);

    BinaryTree *m_tree{};

    int m_xOffsetFactor = 30;
    int m_yOffsetFactor = 2;
};

#endif // TREESCENE_H
