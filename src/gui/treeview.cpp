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
    //fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

void TreeView::updateScene()
{
    treeScene()->redraw();
    //fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

void TreeView::deleteSelectedNodes()
{
    treeScene()->deleteSelectedNodes();
}

TreeScene *TreeView::treeScene() const
{
    return static_cast<TreeScene *>(scene());
}
