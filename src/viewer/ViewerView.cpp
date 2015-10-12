#include "ViewerView.h"
#include <QWidget>
#include <QWheelEvent>
#include <QtMath>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>

ViewerView::ViewerView(QWidget *parent)
    : QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void ViewerView::dragEnterEvent(QDragEnterEvent *e)
{
    auto mimeData = e->mimeData();

    if (mimeData->hasUrls())
    {
        e->acceptProposedAction();
        e->accept();
    }
}

void ViewerView::dragMoveEvent(QDragMoveEvent *e)
{
    // always accept

    e->acceptProposedAction();
    e->accept();
}

void ViewerView::dragLeaveEvent(QDragLeaveEvent *e)
{
    Q_UNUSED(e);
}

void ViewerView::dropEvent(QDropEvent *e)
{
    auto mimeData = e->mimeData();

    // check for our needed mime type, here a file or a list of files
    if (mimeData->hasUrls())
    {
        auto urlList = mimeData->urls();
        auto url = urlList.first();
        auto fileName = url.toLocalFile();

        //importFile(fileName, QPointF(0,0));
        //openFile(fileName);
        emit dropFile(fileName);

        e->acceptProposedAction();
        e->accept();
    }
}

void ViewerView::wheelEvent(QWheelEvent *event)
{
    qreal factor = qPow(1.2, event->delta() / 240.0);
    scale(factor, factor);
    event->accept();
}

