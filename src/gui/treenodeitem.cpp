#include "treenodeitem.h"

#include <QPalette>
#include <QGuiApplication>
#include <QPen>

TreeNodeItem::TreeNodeItem(TreeNode* node, QGraphicsItem* parent)
    :  QGraphicsEllipseItem(parent), m_node(node)
{
    QPalette palette = qApp->palette();
    QColor   textColor = palette.color(QPalette::Text);

    setPen(QPen(textColor));

    setRect(0, 0, 40, 40);
    QGraphicsTextItem* text = new QGraphicsTextItem(QString::number(node->value), this);
    text->setPos(10, 10);
}
