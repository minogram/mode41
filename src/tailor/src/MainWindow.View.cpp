#include "MainWindow.h"
#include <QGraphicsView>

void MainWindow::zoomIn()
{
    m_view->scale(2, 2);
}

void MainWindow::zoomOut()
{
    m_view->scale(0.5, 0.5);
}

void MainWindow::zoomFit()
{
    QRectF rect = m_view->scene()->itemsBoundingRect();

    m_view->fitInView(rect, Qt::AspectRatioMode::KeepAspectRatio);
}
