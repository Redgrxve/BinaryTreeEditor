#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    BinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(8);

    ui->treeView->setTree(tree);
    ui->treeView->drawTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}
