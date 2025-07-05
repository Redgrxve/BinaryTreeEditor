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

    connect(ui->addNodeAction, &QAction::triggered,
            this, &MainWindow::onAddNodeTriggered);
    connect(ui->removeNodeAction, &QAction::triggered,
            this, &MainWindow::onRemoveNodeTriggered);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_tree;
}

void MainWindow::onAddNodeTriggered()
{
    bool ok = false;
    int value = QInputDialog::getInt(this, tr("Вставка нового узла"), tr("Значение: "), 0, INT_MIN, INT_MAX, 1, &ok);
    if (!ok) return;

    if (!m_tree) {
        m_tree = new BinaryTree(value);
        ui->treeView->setTree(m_tree);
        return;
    }

    if (!m_tree->insert(value))
        QMessageBox::critical(this, tr("Ошибка при вставке значения"), tr("Данное значение уже есть в дереве!"));
    else
        ui->treeView->updateScene();
}

void MainWindow::onRemoveNodeTriggered()
{
    ui->treeView->deleteSelectedNodes();
}
