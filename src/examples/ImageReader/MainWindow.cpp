#include "MainWindow.h"
#include <QtCore>
#include <QString>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createUi();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createUi()
{
    QAction *action;
    QMenu *menu;

    // File
    menu = menuBar()->addMenu("&File");
    // File | Open
    action = new QAction(tr("&Open"), this);
    action->setShortcut(QKeySequence::Open);
    connect(action, SIGNAL(triggered()), this, SLOT(open()));
    menu->addAction(action);

    // graphics view
    auto gview = new QGraphicsView(this);
    setCentralWidget(gview);
    // graphics scene
    auto scene = new QGraphicsScene(this);
    gview->setScene(scene);

    //
    setMinimumSize(600, 600);
}

void MainWindow::open()
{
    auto fileName = QFileDialog::getOpenFileName(this, "Open Image", "c:/dev/mode41/test");
    if (!fileName.isEmpty()) {
        openFile(fileName);
    }
}

void MainWindow::openFile(const QString &filePath)
{
    QFileInfo fileInfo(filePath);

    auto scene = qobject_cast<QGraphicsView *>(centralWidget())->scene();
    QImage image;
    if (!image.load(filePath) || image.isNull())
    {
        setWindowTitle(fileInfo.fileName() + " ERR");
        scene->clear();
        return;
    }

    auto pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
    setWindowTitle(fileInfo.fileName());
}
