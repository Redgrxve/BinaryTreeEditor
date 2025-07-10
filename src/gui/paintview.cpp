#include "paintview.h"

#include <QPainter>
#include <qevent.h>

PaintView::PaintView(QWidget *parent)
    : QWidget{parent}, m_image(800, 600, QImage::Format_RGB32)
{
    m_image.fill(Qt::white);
    setAttribute(Qt::WA_AttributeCount);
}

void PaintView::clear()
{
    m_image.fill(Qt::white);
    update();
}

void PaintView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(event->rect(), m_image, event->rect());
}

void PaintView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_lastPoint = event->pos();
        m_isDrawing = true;
    }
}

void PaintView::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && m_isDrawing) {
        drawLineTo(event->pos());
    }
}

void PaintView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_isDrawing) {
        drawLineTo(event->pos());
        m_isDrawing = false;
    }
}

void PaintView::resizeEvent(QResizeEvent *event)
{
    if (width() > m_image.width() || height() > m_image.height()) {
        QImage newImage(size(), QImage::Format_ARGB32);
        newImage.fill(Qt::white);

        QPainter p(&newImage);
        p.drawImage(0, 0, m_image);
        m_image = std::move(newImage);
    }
    QWidget::resizeEvent(event);
}

void PaintView::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&m_image);
    painter.setPen(QPen(m_penColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(m_lastPoint, endPoint);

    update(QRect(m_lastPoint, endPoint).normalized().adjusted(-2, -2, 2, 2));
    m_lastPoint = endPoint;
}
