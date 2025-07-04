#include "treescene.h"
#include "treenodeitem.h"

TreeScene::TreeScene(QObject *parent)
    : QGraphicsScene{parent}
{}

void TreeScene::drawTree(TreeNode *root, int x, int y, int depth)
{
    if (!root) return;

    TreeNodeItem *item = new TreeNodeItem(root);
    addItem(item);
    item->setPos(x, y);

    int offset = 50 * (4 - depth);

    if (root->left) {
        drawTree(root->left, x - offset, y + 80, depth + 1);
        addLine(x + 20, y + 40, x - offset + 20, y + 80);
    }
    if (root->right) {
        drawTree(root->right, x + offset, y + 80, depth + 1);
        addLine(x + 20, y + 40, x + offset + 20, y + 80);
    }

}
