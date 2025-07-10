#include "paintwidget.h"
#include "ui_paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PaintWidget)
{
    ui->setupUi(this);

    connect(ui->colorButton, &QPushButton::clicked,
            this, &PaintWidget::onChangeColor);
    connect(ui->clearButton, &QPushButton::clicked,
            this, &PaintWidget::onClear);
}

PaintWidget::~PaintWidget()
{
    delete ui;
}

void PaintWidget::onChangeColor()
{

}

void PaintWidget::onClear()
{

}
