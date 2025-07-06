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
    void drawFromModel();
    void drawTree(const std::unordered_map<TreeNode *, QPoint> &positions);
    void assignPositions(TreeNode *node, std::unordered_map<TreeNode *, QPoint> &positions, int &currentX, int depth = 0);

    BinaryTree *m_tree{};

    int m_nodeSpacingX = 80;
    int m_nodeSpacingY = 100;

    int m_nodeZValue = 1;
    int m_lineZValue = 0;
};

#endif // TREESCENE_H
