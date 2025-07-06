#include "customgraphicsview.h"

#include <QMouseEvent>
#include <QScrollBar>

CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::NoDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
}

void CustomGraphicsView::setScale(qreal value)
{
    QTransform transform;
    transform.scale(value, value);
    setTransform(transform);

    m_currentScale = value;
    emit scaleChanged(value);
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton ||
        event->button() == Qt::LeftButton && event->modifiers() & Qt::ShiftModifier) {
        m_isDragging = true;
        m_lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragging) {
        QPointF delta = event->pos() - m_lastMousePos;
        m_lastMousePos = event->pos();
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton ||
        event->button() == Qt::LeftButton && event->modifiers() & Qt::ShiftModifier) {
        m_isDragging = false;
        setCursor(Qt::ArrowCursor);
    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void CustomGraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0) {
        const qreal newScale = m_currentScale * m_scaleFactor;
        if (newScale > m_maxScale) return;

        scale(m_scaleFactor, m_scaleFactor);
        m_currentScale = newScale;
    }
    else {
        const qreal newScale = m_currentScale / m_scaleFactor;
        if (newScale < m_minScale) return;

        scale(1.0 / m_scaleFactor, 1.0 / m_scaleFactor);
        m_currentScale = newScale;
    }

    emit scaleChanged(m_currentScale);
}
