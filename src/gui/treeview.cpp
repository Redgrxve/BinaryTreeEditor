#include "treeview.h"
#include "treescene.h"

#include <QKeyEvent>
#include <QTimer>
#include <qwidget.h>

TreeView::TreeView(QWidget *parent)
    : CustomGraphicsView(parent)
{
    auto scene = new TreeScene(this);
    setScene(scene);

    connect(scene, &TreeScene::animationStarted,
            this, &TreeView::onAnimationStarted);
    connect(scene, &TreeScene::animationEnded,
            this, &TreeView::onAnimationEnded);
}

void TreeView::setTree(BinaryTree *tree)
{
    treeScene()->setTree(tree);
}

void TreeView::updateScene()
{
    treeScene()->redraw();
}

void TreeView::deleteSelectedNodes()
{
    treeScene()->deleteSelectedNodes();
}

void TreeView::levelOrderAnimation()
{
    treeScene()->levelOrderAnimated();
}

QVector<QImage> TreeView::levelOrderToImages()
{
    return treeScene()->levelOrderToImages();
}

QImage TreeView::toImage() const
{
    return treeScene()->toImage();
}

TreeScene *TreeView::treeScene() const
{
    return static_cast<TreeScene *>(scene());
}

void TreeView::onAnimationStarted()
{
    setInteractive(false);
    emit animationStarted();
}

void TreeView::onAnimationEnded()
{
    setInteractive(true);
    emit animationEnded();
}
