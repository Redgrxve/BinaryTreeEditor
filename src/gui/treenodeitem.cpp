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

    m_textItem = new QGraphicsTextItem(QString::number(m_node->value), this);
    QFont font = m_textItem->font();
    font.setPointSize(m_fontSize);
    m_textItem->setFont(font);

    setRect(0, 0, m_diameter, m_diameter);

    setupColors();
    setupText();
}

void TreeNodeItem::resetColor()
{
    setPen(m_defaultPenColor);
    setBrush(m_defaultBrushColor);
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
    const QColor color = isSelected() ? m_selectPenColor : m_defaultPenColor;
    setPen(color);

    QGraphicsEllipseItem::paint(painter, option, widget);
}

void TreeNodeItem::setupColors()
{
    const QPalette palette = qApp->palette();
    m_defaultPenColor   = palette.color(QPalette::Text);
    m_defaultBrushColor = palette.color(QPalette::Window);

    setPen(m_defaultPenColor);
    setBrush(m_defaultBrushColor);
}

void TreeNodeItem::setupText()
{
    if (!m_textItem) return;

    const QString text = m_textItem->toPlainText();

    const qreal padding = 3.0;
    const qreal diameter = rect().width();

    QFont font = m_textItem->font();

    for (; m_fontSize >= m_minFontSize; --m_fontSize) {
        font.setPointSize(m_fontSize);
        QFontMetricsF fm(font);

        QRectF textRect = fm.boundingRect(text);
        if (textRect.width() + padding * 2 <= diameter &&
            textRect.height() + padding * 2 <= diameter)
        {
            break;
        }
    }

    font.setPointSize(m_fontSize);
    m_textItem->setFont(font);
    m_textItem->setDefaultTextColor(m_defaultPenColor);

    const QRectF textRect = m_textItem->boundingRect();

    const qreal textPosX = (rect().width() - textRect.width()) * 0.5;
    const qreal textPosY = (rect().height() - textRect.height()) * 0.5;

    m_textItem->setPos(textPosX, textPosY);
}

void TreeNodeItem::setupRect()
{

}
