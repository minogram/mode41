#include "PtnGraphicsView.h"
#include <QMouseEvent>
#include <QWheelEvent>

PtnGraphicsView::PtnGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
}

void PtnGraphicsView::mousePressEvent(QMouseEvent *e)
{
//    m_down = true;
//    m_downView = e->pos();
//    m_downScene = mapToScene(e->pos());
//    e->accept();
}

void PtnGraphicsView::mouseReleaseEvent(QMouseEvent *e)
{
//    m_down = false;
//    e->accept();
}

void PtnGraphicsView::mouseMoveEvent(QMouseEvent *e)
{
//    if (m_down) {
//        //QPoint currView = e->pos();
//        e->accept();
//    }
}

#ifndef QT_NO_WHEELEVENT
void PtnGraphicsView::wheelEvent(QWheelEvent *e)
{
    if (e->delta() > 0) {
        scale(2, 2);
        e->accept();
    } else {
        scale(0.5, 0.5);
        e->accept();
    }
//    if (e->modifiers() & Qt::ControlModifier) {
//        if (e->delta() > 0)
//            view->zoomIn(6);
//        else
//            view->zoomOut(6);
//        e->accept();
//    } else {
//        QGraphicsView::wheelEvent(e);
//    }
}
#endif
