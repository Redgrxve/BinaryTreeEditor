#include "paintwidget.h"
#include "ui_paintwidget.h"

#include <QColorDialog>

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PaintWidget)
{
    ui->setupUi(this);

    updateColorButton();

    connect(ui->colorButton, &QPushButton::clicked,
            this, &PaintWidget::onChangeColor);
    connect(ui->clearButton, &QPushButton::clicked,
            this, &PaintWidget::onClear);
}

PaintWidget::~PaintWidget()
{
    delete ui;
}

void PaintWidget::updateColorButton()
{
    ui->colorButton->setStyleSheet(QString("background-color: %1; border: 1px solid black")
                                       .arg(ui->paintView->penColor().name()));
}

void PaintWidget::onChangeColor()
{
    auto paintView = ui->paintView;
    QColor color = QColorDialog::getColor(paintView->penColor(), this);
    if (color.isValid()) {
        paintView->setPenColor(color);
        updateColorButton();
    }
}

void PaintWidget::onClear()
{
    ui->paintView->clear();
}
