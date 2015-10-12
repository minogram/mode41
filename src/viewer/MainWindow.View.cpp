#include "MainWindow.h"
#include <QMessageBox>
#include <QException>
#include <QGraphicsview>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>

void MainWindow::zoomFit()
{
    auto scene = m_view->scene();

    QRectF rect = scene->itemsBoundingRect();

    m_view->fitInView(rect, Qt::AspectRatioMode::KeepAspectRatio);
}

