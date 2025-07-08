#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class BinaryTree;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadTreeFromFile(const QString &filePath);

private:
    void incrementDepthNumber();
    void updateDepthNumber();
    void removeHint();

    Ui::MainWindow *ui;

    BinaryTree *m_tree{};

    QString m_currentFilePath{};

private slots:
    void onAddNode();
    void onRemoveNode();
    void onDeleteTree();
    void onOpen();
    void onSave();
    void onSaveAs();
    void onCreateReport();

    void onScaleChanged(qreal scale);
    void onSliderMoved(int pos);

    void onAnimationStarted();
    void onAnimationEnded();
};
#endif // MAINWINDOW_H
