#include "MainWindow.h"
#include <QCloseEvent>
#include <QMimeData>

void MainWindow::closeEvent(QCloseEvent *e)
{
    if (maybeSave()) {
        e->accept();
    } else {
        e->ignore();
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    auto mimeData = e->mimeData();

    if (mimeData->hasUrls())
    {
        e->acceptProposedAction();
        e->accept();
    }
}

void MainWindow::dragMoveEvent(QDragMoveEvent *e)
{
    // always accept

    e->acceptProposedAction();
    e->accept();
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *e)
{
    Q_UNUSED(e);
}

void MainWindow::dropEvent(QDropEvent *e)
{
    auto mimeData = e->mimeData();

    // check for our needed mime type, here a file or a list of files
    if (mimeData->hasUrls())
    {
        auto urlList = mimeData->urls();
        auto url = urlList.first();
        auto fileName = url.toLocalFile();

        //importFile(fileName, QPointF(0,0));
        openFile(fileName);

        e->acceptProposedAction();
        e->accept();
    }
}
