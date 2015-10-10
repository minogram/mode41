#include "PtnMainWindow.h"
#include <QCloseEvent>
#include <QMimeData>

void PtnMainWindow::closeEvent(QCloseEvent *e)
{
    if (maybeSave()) {
        e->accept();
    } else {
        e->ignore();
    }
}

void PtnMainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    auto mimeData = e->mimeData();

    if (mimeData->hasUrls())
    {
        e->acceptProposedAction();
        e->accept();
    }
}

void PtnMainWindow::dragMoveEvent(QDragMoveEvent *e)
{
    // always accept

    e->acceptProposedAction();
    e->accept();
}

void PtnMainWindow::dragLeaveEvent(QDragLeaveEvent *e)
{
    Q_UNUSED(e);
}

void PtnMainWindow::dropEvent(QDropEvent *e)
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
