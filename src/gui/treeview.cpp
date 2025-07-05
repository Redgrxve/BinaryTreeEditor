#include "treeview.h"
#include "treenodeitem.h"
#include "treescene.h"

#include <QKeyEvent>

TreeView::TreeView(QWidget *parent)
    : CustomGraphicsView(parent)
{
    auto scene = new TreeScene(this);
    setScene(scene);
}

void TreeView::setTree(BinaryTree *tree)
{
    treeScene()->setTree(tree);
}

void TreeView::drawTree()
{
    treeScene()->drawTree();
}

void TreeView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
        treeScene()->deleteSelectedNodes();
    else
        CustomGraphicsView::keyPressEvent(event);
}

TreeScene *TreeView::treeScene() const
{
    return static_cast<TreeScene *>(scene());
}
