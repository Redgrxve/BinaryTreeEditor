#include "treescene.h"
#include "treenodeitem.h"

TreeScene::TreeScene(QObject *parent)
    : QGraphicsScene{parent}
{}

void TreeScene::setTree(BinaryTree *tree)
{
    m_tree = tree;
    redraw();
}

void TreeScene::redraw()
{
    clear();
    draw();
}

void TreeScene::draw()
{
    if (!m_tree) return;

    const int maxDepth = m_tree->depth();
    drawTree(m_tree->root(), maxDepth);
}

void TreeScene::drawTree(TreeNode *root, int maxDepth, int x, int y, int depth)
{
    if (!root) return;

    auto item = new TreeNodeItem(root);
    item->setPos(x, y);
    addItem(item);

    const qreal w = item->width();
    const qreal h = item->height();

    const int xOffset = m_xOffsetFactor * (maxDepth - depth);
    const int yOffset = w * m_yOffsetFactor;

    if (root->left) {
        drawTree(root->left, maxDepth, x - xOffset, y + yOffset, depth + 1);

        const qreal x1 = x + w * 0.5;
        const qreal y1 = y + h;
        const qreal x2 = x - xOffset + w * 0.5;
        const qreal y2 = y + yOffset;
        addLine(x1, y1, x2, y2, item->pen());
    }
    if (root->right) {
        drawTree(root->right, maxDepth, x + xOffset, y + yOffset, depth + 1);

        const qreal x1 = x + w * 0.5;
        const qreal y1 = y + h;
        const qreal x2 = x + xOffset + w * 0.5;
        const qreal y2 = y + yOffset;
        addLine(x1, y1, x2, y2, item->pen());
    }

}

void TreeScene::deleteSelectedNodes()
{
    if (!m_tree) return;

    const QList<QGraphicsItem *> selected = selectedItems();
    if (selected.empty()) return;

    for (QGraphicsItem *item : selected) {
        const auto nodeItem = qgraphicsitem_cast<TreeNodeItem *>(item);
        if (!nodeItem) return;

        removeItem(nodeItem);
        m_tree->remove(nodeItem->node()->value);
        delete nodeItem;
    }

    redraw();
}
