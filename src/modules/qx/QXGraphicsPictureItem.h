#ifndef QGRAPHICSPICTUREITEM_H
#define QGRAPHICSPICTUREITEM_H

#include <QGraphicsItem>
#include <QPicture>
#include <QRectF>

class QXGraphicsPictureItem : public QGraphicsItem
{
public:
    QXGraphicsPictureItem(const QPicture &picture, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    // overriding paint()
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:

public slots:

private:
    QPicture m_picture;
};

#endif // QGRAPHICSPICTUREITEM_H
