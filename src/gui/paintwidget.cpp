#include "paintwidget.h"
#include "ui_paintwidget.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QImageReader>
#include <QMessageBox>

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
    connect(ui->openButton, &QPushButton::clicked,
            this, &PaintWidget::onOpen);
    connect(ui->saveButton, &QPushButton::clicked,
            this, &PaintWidget::onSave);
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

void PaintWidget::onOpen()
{
    const QString filePath = QFileDialog::getOpenFileName(this, tr("Открыть файл изображения"), "", tr("Изображения (*.png *.jpg *.bmp)"));
    if (filePath.isEmpty()) return;

    if (!ui->paintView->loadImage(filePath)) {
        QMessageBox::critical(this, tr("Ошибка при открытии изображения"), tr("Не удалось открыть изображение"));
    }
}

void PaintWidget::onSave()
{

}
