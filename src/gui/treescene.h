#ifndef TREESCENE_H
#define TREESCENE_H

#include "binarytree.h"
#include <QGraphicsScene>
#include <QHash>

class TreeNodeItem;

class TreeScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit TreeScene(QObject *parent = nullptr);

    void setTree(BinaryTree *tree);

    void redraw();
    void draw();

    void deleteAllNodes();
    void deleteSelectedNodes();

    void levelOrder(std::function<void(TreeNodeItem *)> handle);
    void levelOrderAnimated();
    void resetNodesColor();

private:
    void drawFromModel();
    void drawTree(const std::unordered_map<TreeNode *, QPoint> &positions);
    void assignPositions(TreeNode *node, std::unordered_map<TreeNode *, QPoint> &positions, int &currentX, int depth = 0);
    void deleteNodeItem(TreeNodeItem *nodeItem);

    BinaryTree *m_tree{};

    QHash<TreeNode *, TreeNodeItem *> m_nodeMap;

    int m_nodeSpacingX = 80;
    int m_nodeSpacingY = 100;

    int m_nodeZValue = 1;
    int m_lineZValue = 0;

    int m_animationDelay = 300;

    QColor m_levelOrderColor = Qt::blue;

signals:
    void animationStarted();
    void animationEnded();

private slots:
    void onAnimationStarted();
    void onAnimationEnded();
};

#endif // TREESCENE_H
