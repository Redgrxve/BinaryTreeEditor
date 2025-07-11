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

    void updateColorButton();

private slots:
    void onChangeColor();
    void onClear();
    void onOpen();
    void onSave();
};

#endif // PAINTWIDGET_H
