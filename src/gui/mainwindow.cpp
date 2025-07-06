#include "mainwindow.h"
#include "jsonserializer.h"
#include "utils.h"
#include "ui_mainwindow.h"

#include <QGraphicsEllipseItem>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextBrowser>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->depthLcdNumber->setPalette(qApp->palette().color(QPalette::Text));

    // TreeNode *root = JsonSerializer::loadFromFile("tree.json");
    // m_tree = new BinaryTree(root);
    // ui->treeView->setTree(m_tree);

    connect(ui->addNodeAction, &QAction::triggered,
            this, &MainWindow::onAddNodeTriggered);
    connect(ui->removeNodeAction, &QAction::triggered,
            this, &MainWindow::onRemoveNodeTriggered);
    connect(ui->deleteTreeAction, &QAction::triggered,
            this, &MainWindow::onDeleteTreeTriggered);
    connect(ui->levelOrderAction, &QAction::triggered,
            this, [this](){ui->treeView->levelOrderAnimation();});
    connect(ui->openAction, &QAction::triggered,
            this, &MainWindow::onOpenTriggered);
    connect(ui->saveAction, &QAction::triggered,
            this, &MainWindow::onSaveTriggered);
    connect(ui->saveAsAction, &QAction::triggered,
            this, &MainWindow::onSaveAsTriggered);
    connect(ui->createReportAction, &QAction::triggered,
            this, &MainWindow::onReportTriggered);

    connect(ui->treeView, &TreeView::scaleChanged,
            this, &MainWindow::onScaleChanged);
    connect(ui->scaleSlider, &QSlider::sliderMoved,
            this, &MainWindow::onSliderMoved);

    connect(ui->treeView, &TreeView::animationStarted,
            this, &MainWindow::onAnimationStarted);
    connect(ui->treeView, &TreeView::animationEnded,
            this, &MainWindow::onAnimationEnded);
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

void MainWindow::onDeleteTreeTriggered()
{
    if (!m_tree) return;

    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Подтверждение удаления",
                                                              "Вы действительно хотите удалить дерево?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) return;

    m_tree->clear();
    ui->treeView->updateScene();
    updateDepthNumber();
}

void MainWindow::onOpenTriggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Открыть файл дерева"), "", tr("JSON файлы (*.json)"));
    if (filePath.isEmpty()) return;

    TreeNode *root = JsonSerializer::loadFromFile(filePath);
    if (!root) return;

    if (m_tree)
        delete m_tree;

    m_tree = new BinaryTree(root);
    ui->treeView->setTree(m_tree);

    m_currentFilePath = filePath;
    updateDepthNumber();
    ui->statusbar->showMessage(tr("Загружен файл: ") + filePath);
}

void MainWindow::onSaveTriggered()
{
    if (!m_tree) return;

    if (m_currentFilePath.isEmpty()) {
        onSaveAsTriggered();
        return;
    }

    if (JsonSerializer::saveToFile(m_tree->root(), m_currentFilePath))
        ui->statusbar->showMessage(tr("Сохранен файл: ") + m_currentFilePath);
    else
        QMessageBox::critical(this, tr("Ошибка при сохранении файла"), tr("Не удалось открыть файл"));
}

void MainWindow::onSaveAsTriggered()
{
    if (!m_tree) return;

    QString filePath = QFileDialog::getSaveFileName(this, tr("Открыть файл дерева"), "tree.json", tr("JSON файл (*.json)"));
    if (filePath.isEmpty()) return;

    if (JsonSerializer::saveToFile(m_tree->root(), filePath)) {
        m_currentFilePath = filePath;
        ui->statusbar->showMessage(tr("Сохранен файл: ") + m_currentFilePath);
    }
    else {
        QMessageBox::critical(this, tr("Ошибка при сохранении файла"), tr("Не удалось создать файл"));
    }
}

void MainWindow::onReportTriggered()
{
    QVector<QImage> images = ui->treeView->levelOrderToImages();
    if (images.empty()) return;

    for (int i = 0; i < images.size(); ++i) {
        images[i].save(QString("l%1.png").arg(i), "PNG", 100);
    }

    QString html = R"(
                    <!DOCTYPE html>
                    <html>
                    <head><meta charset="UTF-8"><title>Обход в ширину</title></head>
                    <body style="font-family: sans-serif; text-align: center;">
                    <h1>Обход в ширину</h1>
                    <h1><h1>
    )";
    for (const auto &img : std::as_const(images)) {
        html.append(htmlImgTagFromImage(img) + "\n");
    }
    html.append("</body>\n</html>");

    const QString fileName = "levelOrder.html";
    if (!saveHtmlToFile(html, fileName)) {
        QMessageBox::critical(this, tr("Ошибка при создании отчета"), tr("Не удалось создать отчет"));
        return;
    }

    ui->statusbar->showMessage(tr("Создан отчет: ") + fileName);

    auto textBrowser = new QTextBrowser;
    textBrowser->setWindowTitle("Отчет");
    textBrowser->setSource(fileName);
    textBrowser->showMaximized();
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

void MainWindow::onAnimationStarted()
{
    ui->addNodeAction->setEnabled(false);
    ui->removeNodeAction->setEnabled(false);
    ui->deleteTreeAction->setEnabled(false);
    ui->levelOrderAction->setEnabled(false);
    ui->createReportAction->setEnabled(false);
    ui->openAction->setEnabled(false);
}

void MainWindow::onAnimationEnded()
{
    ui->addNodeAction->setEnabled(true);
    ui->removeNodeAction->setEnabled(true);
    ui->deleteTreeAction->setEnabled(true);
    ui->levelOrderAction->setEnabled(true);
    ui->createReportAction->setEnabled(true);
    ui->openAction->setEnabled(true);
}
