#include "treescene.h"
#include "treenodeitem.h"

#include <QGuiApplication>
#include <QPalette>

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

    drawFromModel();
    setSceneRect(itemsBoundingRect());
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

void TreeScene::drawFromModel()
{
    int currentX = 0;
    std::unordered_map<TreeNode *, QPoint> positions;
    assignPositions(m_tree->root(), positions, currentX);
    drawTree(positions);
}

void TreeScene::drawTree(const std::unordered_map<TreeNode *, QPoint> &positions)
{
    std::unordered_map<TreeNode *, TreeNodeItem *> items;

    for (const auto &[node, pos] : positions) {
        const int x = pos.x() * m_nodeSpacingX;
        const int y = pos.y() * m_nodeSpacingY;

        auto item = new TreeNodeItem(node);
        item->setPos(x, y);
        addItem(item);
        items[node] = item;
    }

    const QPen pen(qApp->palette().color(QPalette::Text));
    for (const auto &[node, pos] : positions) {
        if (node->left) {
            QLineF line(items[node]->center(), items[node->left]->center());
            addLine(line, pen);
        }
        if (node->right) {
            QLineF line(items[node]->center(), items[node->right]->center());
            addLine(line, pen);
        }
    }
}

void TreeScene::assignPositions(TreeNode *node, std::unordered_map<TreeNode *, QPoint> &positions, int &currentX, int depth)
{
    if (!node) return;

    assignPositions(node->left, positions, currentX, depth + 1);

    positions[node] = QPoint(currentX++, depth);

    assignPositions(node->right, positions, currentX, depth + 1);
}

