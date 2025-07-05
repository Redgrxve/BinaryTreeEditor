#ifndef TREENODEITEM_H
#define TREENODEITEM_H

#include <QGraphicsEllipseItem>

#include "binarytree.h"

class TreeNodeItem : public QGraphicsEllipseItem
{
public:
    explicit TreeNodeItem(TreeNode* node, QGraphicsItem* parent = nullptr);

    inline TreeNode *node() const { return m_node; }

    inline qreal width()  const { return rect().width(); }
    inline qreal height() const { return rect().height(); }

    inline QGraphicsTextItem *textItem() const { return m_textItem; }

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    void setupColors();

    TreeNode *m_node;
    QGraphicsTextItem *m_textItem;

    qreal m_width  = 40.0;
    qreal m_height = 40.0;

    QColor m_defaultColor = Qt::black;
    QColor m_selectColor  = Qt::red;
};

#endif // TREENODEITEM_H
