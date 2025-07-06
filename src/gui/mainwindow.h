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

private:
    void incrementDepthNumber();
    void updateDepthNumber();

    Ui::MainWindow *ui;

    BinaryTree *m_tree{};

    QString m_currentFilePath{};

private slots:
    void onAddNodeTriggered();
    void onRemoveNodeTriggered();
    void onDeleteTreeTriggered();
    void onOpenTriggered();
    void onSaveTriggered();
    void onSaveAsTriggered();
    void onReportTriggered();

    void onScaleChanged(qreal scale);
    void onSliderMoved(int pos);

    void onAnimationStarted();
    void onAnimationEnded();
};
#endif // MAINWINDOW_H
