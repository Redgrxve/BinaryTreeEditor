#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "customgraphicsview.h"
#include "binarytree.h"

class TreeScene;

class TreeView : public CustomGraphicsView
{
    Q_OBJECT

public:
    explicit TreeView(QWidget *parent = nullptr);

    void setTree(BinaryTree *tree);
    void updateScene();
    void deleteSelectedNodes();
    void levelOrderAnimation();

    QVector<QImage> levelOrderToImages();
    QImage toImage() const;

private:
    TreeScene *treeScene() const;

signals:
    void animationStarted();
    void animationEnded();

private slots:
    void onAnimationStarted();
    void onAnimationEnded();
};


#endif // TREEVIEW_H
