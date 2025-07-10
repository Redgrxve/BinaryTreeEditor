#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <QWidget>

class PaintView : public QWidget
{
    Q_OBJECT
public:
    explicit PaintView(QWidget *parent = nullptr);

    inline void setPenColor(const QColor &color) { m_penColor = color; }
    inline const QColor &penColor() const { return m_penColor; }

    void clear();

protected:
    void paintEvent(QPaintEvent *event)        override;
    void mousePressEvent(QMouseEvent *event)   override;
    void mouseMoveEvent(QMouseEvent *event)    override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event)      override;

private:
    void drawLineTo(const QPoint &endPoint);

    QImage m_image;
    QPoint m_lastPoint;
    QColor m_penColor = Qt::black;
    bool m_isDrawing = false;
};

#endif // PAINTVIEW_H
