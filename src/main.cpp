#include "mainwindow.h"
#include "binarytree.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // BinaryTree tree;
    // tree.insert(5);
    // tree.insert(3);
    // tree.insert(7);
    // tree.insert(2);
    // tree.insert(4);
    // tree.insert(8);

    // tree.remove(3);

    // return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
