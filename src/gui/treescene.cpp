#include "treescene.h"
#include "treenodeitem.h"

#include <vector>

#include <QGuiApplication>
#include <QPalette>
#include <QQueue>
#include <QTimer>

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
    m_nodeMap.clear();
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

        deleteNodeItem(nodeItem);
    }

    redraw();
}

void TreeScene::levelOrderAnimated()
{
    if (!m_tree || !m_tree->root()) return;

    std::vector<TreeNode *> nodes;
    nodes.reserve(m_nodeMap.size());
    const auto handler = [&nodes](TreeNode *node) {
        nodes.push_back(node);
    };

    m_tree->levelOrder(handler);

    auto timer = new QTimer(this);
    int index = 0;

    clearSelection();
    emit animationStarted();

    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (index >= nodes.size()) {
            timer->stop();
            timer->deleteLater();

            redraw();
            emit animationEnded();

            return;
        }

        TreeNode* node = nodes[index];
        if (m_nodeMap.contains(node)) {
            m_nodeMap[node]->setBrush(QBrush(Qt::blue));
        }

        ++index;
    });

    timer->start(m_animationDelay);
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
    for (const auto &[node, pos] : positions) {
        const int x = pos.x() * m_nodeSpacingX;
        const int y = pos.y() * m_nodeSpacingY;

        auto item = new TreeNodeItem(node);
        item->setPos(x, y);
        item->setZValue(m_nodeZValue);
        addItem(item);
        if (!m_nodeMap.contains(node))
            m_nodeMap[node] = item;
    }

    const QPen pen(qApp->palette().color(QPalette::Text));
    for (const auto &[node, pos] : positions) {
        if (node->left) {
            const QLineF lineF(m_nodeMap[node]->center(), m_nodeMap[node->left]->center());
            auto line = addLine(lineF, pen);
            line->setZValue(m_lineZValue);
        }
        if (node->right) {
            const QLineF lineF(m_nodeMap[node]->center(), m_nodeMap[node->right]->center());
            auto line = addLine(lineF, pen);
            line->setZValue(m_lineZValue);
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

void TreeScene::deleteNodeItem(TreeNodeItem *nodeItem)
{
    TreeNode *node = nodeItem->node();
    if (!m_nodeMap.contains(node)) return;

    removeItem(nodeItem);
    m_tree->remove(node->value);
    m_nodeMap.remove(node);
    delete nodeItem;
}

