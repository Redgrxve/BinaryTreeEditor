#ifndef TREENODEITEM_H
#define TREENODEITEM_H

#include <QGraphicsEllipseItem>

#include "binarytree.h"

class TreeNodeItem : public QGraphicsEllipseItem
{
public:
    explicit TreeNodeItem(TreeNode* node, QGraphicsItem* parent = nullptr);

    inline TreeNode *node() const { return m_node; }

    inline QPointF center() const { return pos() + boundingRect().center(); }
    inline qreal width()    const { return boundingRect().width(); }
    inline qreal height()   const { return boundingRect().height(); }

    inline QGraphicsTextItem *textItem() const { return m_textItem; }

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    void setupColors();
    void setupText();
    void setupRect();

    TreeNode *m_node{};
    QGraphicsTextItem *m_textItem{};

    QColor m_defaultPenColor = Qt::black;
    QColor m_selectPenColor  = Qt::red;

    qreal m_textMargin = 5.0;
};

#endif // TREENODEITEM_H
