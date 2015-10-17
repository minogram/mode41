#ifndef VIEWERVIEW_H
#define VIEWERVIEW_H

#include <QGraphicsView>

class QWidget;

class ViewerView : public QGraphicsView
{
    Q_OBJECT

public:
    ViewerView(QWidget *parent = 0);

protected:
    void dragEnterEvent(QDragEnterEvent *e) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *e) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *e) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *e) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    //void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

public:
signals:
    void dropFile(const QString &fileName);

public slots:
};

#endif // VIEWERVIEW_H
