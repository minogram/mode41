#ifndef PTNGRAPHICSVIEW_H
#define PTNGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QPoint>
#include <QPointF>

class QMouseEvent;

class PtnGraphicsView : public QGraphicsView
{
public:
    PtnGraphicsView(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *e) Q_DECL_OVERRIDE;
#endif

signals:

public slots:

private:
    QPoint m_downView;
    QPointF m_downScene;
    bool m_down = false;
};

#endif // PTNGRAPHICSVIEW_H
