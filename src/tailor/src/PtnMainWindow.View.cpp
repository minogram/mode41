#include "PtnMainWindow.h"
#include <QGraphicsView>

void PtnMainWindow::zoomIn()
{
    m_view->scale(2, 2);
}

void PtnMainWindow::zoomOut()
{
    m_view->scale(0.5, 0.5);
}

void PtnMainWindow::zoomFit()
{
    QRectF rect = m_view->scene()->itemsBoundingRect();

    m_view->fitInView(rect, Qt::AspectRatioMode::KeepAspectRatio);
}
