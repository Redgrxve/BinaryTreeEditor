#include "treenodeitem.h"

#include <QPalette>
#include <QGuiApplication>
#include <QPen>
#include <QCursor>
#include <QPainter>

TreeNodeItem::TreeNodeItem(TreeNode* node, QGraphicsItem* parent)
    :  QGraphicsEllipseItem(parent), m_node(node)
{
    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIsSelectable);
    setupColors();

    setRect(0, 0, m_width, m_height);

    m_textItem = new QGraphicsTextItem(QString::number(node->value), this);
    m_textItem->setDefaultTextColor(pen().color());

    const QRectF textRect = m_textItem->boundingRect();
    const qreal  textPosX = (m_width - textRect.width()) * 0.5;
    const qreal  textPosY = (m_height - textRect.height()) * 0.5;

    m_textItem->setPos(textPosX, textPosY);
}

void TreeNodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::PointingHandCursor);

    QGraphicsEllipseItem::hoverEnterEvent(event);
}

void TreeNodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::ArrowCursor);

    QGraphicsEllipseItem::hoverLeaveEvent(event);
}

void TreeNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor color = isSelected() ? m_selectColor : m_defaultColor;
    setPen(color);

    QGraphicsEllipseItem::paint(painter, option, widget);
}

void TreeNodeItem::setupColors()
{
    const QPalette palette = qApp->palette();
    const QColor   color   = palette.color(QPalette::Text);

    m_defaultColor = color;
    setPen(color);
}
