#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CustomGraphicsView(QWidget *parent = nullptr);

    void setScale(qreal value);

protected:
    void mousePressEvent(QMouseEvent *event)   override;
    void mouseMoveEvent(QMouseEvent *event)    override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event)        override;

private:
    qreal m_currentScale = 1.0;
    qreal m_scaleFactor  = 1.2;
    qreal m_maxScale     = 4.0;
    qreal m_minScale     = 0.1;

    bool m_isDragging = false;
    QPoint m_lastMousePos;

signals:
    void scaleChanged(qreal scale);
};

#endif // CUSTOMGRAPHICSVIEW_H
