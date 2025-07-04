#include "treeview.h"
#include "treescene.h"

TreeView::TreeView(QWidget *parent)
    : CustomGraphicsView(parent)
{
    auto scene = new TreeScene(this);
    setScene(scene);
}

void TreeView::drawTree()
{
    m_scene->drawTree(m_tree.root());
}
