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

    void resetColor();

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

    QColor m_defaultBrushColor = Qt::white;
    QColor m_defaultPenColor = Qt::black;
    QColor m_selectPenColor  = Qt::red;

    int m_diameter = 80;

    int m_fontSize = 16;
    int m_minFontSize = 6;
};

#endif // TREENODEITEM_H
