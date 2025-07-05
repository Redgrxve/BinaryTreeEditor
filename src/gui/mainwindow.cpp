#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_tree = new BinaryTree;
    m_tree->insert(5);
    m_tree->insert(3);
    m_tree->insert(7);
    m_tree->insert(2);
    m_tree->insert(4);
    m_tree->insert(8);
    m_tree->insert(9);
    m_tree->insert(-1);
    m_tree->insert(-3);
    m_tree->insert(10);
    m_tree->insert(12);
    m_tree->insert(11);

    ui->treeView->setTree(m_tree);
    ui->treeView->drawTree();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_tree;
}
