#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

namespace Ui {
class PaintWidget;
}

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PaintWidget(QWidget *parent = nullptr);
    ~PaintWidget();

private:
    Ui::PaintWidget *ui;

private slots:
    void onChangeColor();
    void onClear();
};

#endif // PAINTWIDGET_H
