#ifndef TREESCENE_H
#define TREESCENE_H

#include "binarytree.h"
#include <QGraphicsScene>

class TreeScene : public QGraphicsScene
{
public:
    explicit TreeScene(QObject *parent = nullptr);

    void drawTree(TreeNode *root, int x = 0, int y = 0, int depth = 0);
};

#endif // TREESCENE_H
