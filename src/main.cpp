#include "binarytree.h"
#include "mainwindow.h"
#include "paintwidget.h".h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator qtTranslator;
    if (qtTranslator.load("qtbase_ru", QLibraryInfo::path(QLibraryInfo::TranslationsPath))) {
        a.installTranslator(&qtTranslator);
    }

    PaintWidget w;
    // MainWindow w;
    // if (a.arguments().count() > 1) {
    //     QString filePath = a.arguments().at(1);;
    //     w.loadTreeFromFile(filePath);
    // }

    w.show();
    return a.exec();
}
