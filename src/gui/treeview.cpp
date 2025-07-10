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
