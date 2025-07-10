#include "mainwindow.h"
#include "jsonserializer.h"
#include "utils.h"
#include "paintwidget.h"
#include "ui_mainwindow.h"

#include <QGraphicsEllipseItem>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextBrowser>
#include <QWebEngineView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->depthLcdNumber->setPalette(qApp->palette().color(QPalette::Text));

    connect(ui->addNodeAction, &QAction::triggered,
            this, &MainWindow::onAddNode);
    connect(ui->removeNodeAction, &QAction::triggered,
            this, &MainWindow::onRemoveNode);
    connect(ui->deleteTreeAction, &QAction::triggered,
            this, &MainWindow::onDeleteTree);
    connect(ui->levelOrderAction, &QAction::triggered,
            this, [this](){ui->treeView->levelOrderAnimation();});
    connect(ui->openAction, &QAction::triggered,
            this, &MainWindow::onOpen);
    connect(ui->saveAction, &QAction::triggered,
            this, &MainWindow::onSave);
    connect(ui->saveAsAction, &QAction::triggered,
            this, &MainWindow::onSaveAs);
    connect(ui->createReportAction, &QAction::triggered,
            this, &MainWindow::onCreateReport);
    connect(ui->openReportAction, &QAction::triggered,
            this, &MainWindow::onOpenReport);
    connect(ui->paintAction, &QAction::triggered,
            this, &MainWindow::onPaint);

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

void MainWindow::loadTreeFromFile(const QString &filePath)
{
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
    removeHint();
}

void MainWindow::openReportInWebView(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists()) {
        QMessageBox::critical(this, "Ошибка", "Файл отчёта не найден!");
        return;
    }

    auto webView = new QWebEngineView();
    webView->setAttribute(Qt::WA_DeleteOnClose);
    webView->setWindowTitle("Отчет");
    webView->load(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
    webView->showMaximized();
}

QString MainWindow::generateHtmlReport()
{
    QImage initialImage = ui->treeView->toImage();
    QVector<QImage> stepImages = ui->treeView->levelOrderToImages();
    if (stepImages.empty()) return QString();

    const int depth = ui->depthLcdNumber->intValue();
    const QDateTime time = QDateTime::currentDateTime();

    QString html = QString(R"(
        <!DOCTYPE html>
        <html>
        <head>
            <meta charset="UTF-8">
            <title>Обход в ширину</title>
            <style>
                @import url('https://fonts.googleapis.com/css2?family=Roboto:ital,wght@0,100..900;1,100..900&display=swap');
                body { font-family: 'Roboto', sans-serif; }
                .info { background-color: #bdc3c7; padding: 10px 20px;}
                h1, h2 { color: #2980b9; text-align: center;}
                .step { text-align: center; }
            </style>
        </head>
        <body>
            <h1>Отчет об обходе бинарного дерева</h1>
            <div class="info">
                <p>Глубина дерева: %1</p>
                <p>Тип обхода: в ширину (по уровням)</p>
                <p>Дата создания: %2</p>
            </div>
            <div class="step">
                <h2>Исходное дерево</h2>
                %3
                <h2>Процесс обхода</h2>
            </div>
    )").arg(QString::number(depth), time.toString("dd.MM.yyyy HH:mm"), htmlImgTagFromImage(initialImage));
    for (int i = 0; i < stepImages.size(); ++i) {
        const QString step = QString(R"(
            <div class="step">
                <h3>Уровень %1</h3>
                %2
            </div>
        )").arg(QString::number(i + 1), htmlImgTagFromImage(stepImages[i]));
        html.append(step);
    }
    html.append("</body>\n</html>");

    return html;
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

void MainWindow::removeHint()
{
    if (!ui->hintLabel) return;

    delete ui->hintLabel;
    ui->hintLabel = nullptr;
}

void MainWindow::onAddNode()
{
    bool ok = false;
    int value = QInputDialog::getInt(this, tr("Вставка нового узла"), tr("Значение: "), 0, INT_MIN, INT_MAX, 1, &ok);
    if (!ok) return;

    if (!m_tree) {
        m_tree = new BinaryTree(value);
        ui->treeView->setTree(m_tree);
        updateDepthNumber();
        removeHint();
        return;
    }

    if (!m_tree->insert(value))
        QMessageBox::critical(this, tr("Ошибка при вставке значения"), tr("Данное значение уже есть в дереве!"));
    else {
        ui->treeView->updateScene();
        updateDepthNumber();
        removeHint();
    }
}

void MainWindow::onRemoveNode()
{
    if (!m_tree || !m_tree->root())
        return;

    if (!ui->treeView->isItemsSelected()) {
        bool ok = false;
        int value = QInputDialog::getInt(this, tr("Удаление узла"), tr("Значение удаляемого узла: "), 0, INT_MIN, INT_MAX, 1, &ok);
        if (!ok) return;

        if (!m_tree->remove(value)) {
            QMessageBox::critical(this, tr("Ошибка при удалении узла"), tr("Такого узла нет в дереве"));
            return;
        }

        ui->treeView->updateScene();
        updateDepthNumber();
    } else {
        ui->treeView->deleteSelectedNodes();
        updateDepthNumber();
    }
}

void MainWindow::onDeleteTree()
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

void MainWindow::onOpen()
{
    const QString filePath = QFileDialog::getOpenFileName(this, tr("Открыть файл дерева"), "", tr("BinTree файл (*.btr)"));
    loadTreeFromFile(filePath);
}

void MainWindow::onSave()
{
    if (!m_tree) return;

    if (m_currentFilePath.isEmpty()) {
        onSaveAs();
        return;
    }

    if (JsonSerializer::saveToFile(m_tree->root(), m_currentFilePath))
        ui->statusbar->showMessage(tr("Сохранен файл: ") + m_currentFilePath);
    else
        QMessageBox::critical(this, tr("Ошибка при сохранении файла"), tr("Не удалось открыть файл"));
}

void MainWindow::onSaveAs()
{
    if (!m_tree) return;

    const QString filePath = QFileDialog::getSaveFileName(this, tr("Сохранить файл дерева"), "tree.btr", tr("BinTree файл (*.btr)"));
    if (filePath.isEmpty()) return;

    if (JsonSerializer::saveToFile(m_tree->root(), filePath)) {
        m_currentFilePath = filePath;
        ui->statusbar->showMessage(tr("Сохранен файл: ") + m_currentFilePath);
    }
    else {
        QMessageBox::critical(this, tr("Ошибка при сохранении файла"), tr("Не удалось создать файл"));
    }
}

void MainWindow::onCreateReport()
{
    const QString html = generateHtmlReport();
    if (html.isEmpty()) {
        QMessageBox::warning(this, tr("Предупреждение"), tr("Перед созданием отчета необходимо заполнить дерево"));
        return;
    }

    const QString filePath = QFileDialog::getSaveFileName(this, tr("Сохранить отчет"), "report.html", tr("HTML-файл (*.html)"));
    if (filePath.isEmpty()) return;

    if (!saveHtmlToFile(html, filePath)) {
        QMessageBox::critical(this, tr("Ошибка при сохранении отчета"), tr("Не удалось сохранить отчет"));
        return;
    }

    ui->statusbar->showMessage(tr("Создан отчет: ") + filePath);

    openReportInWebView(filePath);
}

void MainWindow::onOpenReport()
{
    const QString filePath = QFileDialog::getOpenFileName(this, tr("Открыть файл отчета"), "", tr("HTML-файл (*.html)"));
    if (filePath.isEmpty()) return;

    openReportInWebView(filePath);
}

void MainWindow::onPaint()
{
    auto *paintWidget = new PaintWidget;
    paintWidget->setAttribute(Qt::WA_DeleteOnClose);
    paintWidget->show();
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
