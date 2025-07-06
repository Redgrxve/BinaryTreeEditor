#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsEllipseItem>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->depthLcdNumber->setPalette(qApp->palette().color(QPalette::Text));

    connect(ui->addNodeAction, &QAction::triggered,
            this, &MainWindow::onAddNodeTriggered);
    connect(ui->removeNodeAction, &QAction::triggered,
            this, &MainWindow::onRemoveNodeTriggered);
    connect(ui->treeView, &TreeView::scaleChanged,
            this, &MainWindow::onScaleChanged);
    connect(ui->scaleSlider, &QSlider::sliderMoved,
            this, &MainWindow::onSliderMoved);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_tree;
}

void MainWindow::incrementDepthNumber()
{
    const int curr = ui->depthLcdNumber->intValue();
    ui->depthLcdNumber->display(curr + 1);
}

void MainWindow::updateDepthNumber()
{
    ui->depthLcdNumber->display(m_tree->depth());
}

void MainWindow::onAddNodeTriggered()
{
    bool ok = false;
    int value = QInputDialog::getInt(this, tr("Вставка нового узла"), tr("Значение: "), 0, INT_MIN, INT_MAX, 1, &ok);
    if (!ok) return;

    if (!m_tree) {
        m_tree = new BinaryTree(value);
        ui->treeView->setTree(m_tree);
        updateDepthNumber();
        return;
    }

    if (!m_tree->insert(value))
        QMessageBox::critical(this, tr("Ошибка при вставке значения"), tr("Данное значение уже есть в дереве!"));
    else {
        ui->treeView->updateScene();
        updateDepthNumber();
    }
}

void MainWindow::onRemoveNodeTriggered()
{
    ui->treeView->deleteSelectedNodes();
    updateDepthNumber();
}

void MainWindow::onScaleChanged(qreal scale)
{
    const int value = static_cast<int>(scale * 100.0);
    ui->scaleSlider->setValue(value);
    ui->scaleLabel->setText(QString::number(value) + "%");
}

void MainWindow::onSliderMoved(int pos)
{
    ui->treeView->setScale(pos / 100.0);
}
