#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "customgraphicsview.h"
#include "treescene.h"

class TreeScene;
class TreeNodeItem;

class TreeView : public CustomGraphicsView
{
    Q_OBJECT

public:
    explicit TreeView(QWidget *parent = nullptr);

    inline void setTree(BinaryTree *tree) {
        treeScene()->setTree(tree);
    }

    inline void updateScene() {
        treeScene()->redraw();
    }

    inline void deleteSelectedNodes() {
        treeScene()->deleteSelectedNodes();
    }

    inline void levelOrderAnimation() {
        treeScene()->levelOrderAnimated();
    }

    inline QVector<QGraphicsItem *> selectedItems() const {
        return scene()->selectedItems();
    }

    inline bool isItemsSelected() const {
        return !scene()->selectedItems().isEmpty();
    }

    inline QVector<QImage> levelOrderToImages() const {
        return treeScene()->levelOrderToImages();
    }

    inline QImage toImage() const {
        return treeScene()->toImage();
    }

private:
    inline TreeScene *treeScene() const {
        return static_cast<TreeScene *>(scene());
    }

signals:
    void animationStarted();
    void animationEnded();

private slots:
    void onAnimationStarted();
    void onAnimationEnded();
};


#endif // TREEVIEW_H
