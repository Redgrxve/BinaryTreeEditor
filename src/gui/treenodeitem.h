#ifndef TREENODEITEM_H
#define TREENODEITEM_H

#include <QGraphicsEllipseItem>

#include "binarytree.h"

class TreeNodeItem : public QGraphicsEllipseItem
{
public:
    explicit TreeNodeItem(TreeNode* node, QGraphicsItem* parent = nullptr);

private:
    TreeNode *m_node;
};

#endif // TREENODEITEM_H
