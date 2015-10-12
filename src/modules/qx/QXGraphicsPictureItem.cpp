#include "QXGraphicsPictureItem.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

QXGraphicsPictureItem::QXGraphicsPictureItem(const QPicture &picture, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , m_picture(picture)
{
}

QRectF QXGraphicsPictureItem::boundingRect() const
{
    return m_picture.boundingRect();
}

void QXGraphicsPictureItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QRectF rect = boundingRect();

//    if(Pressed)
//    {
//        QPen pen(Qt::red, 3);
//        painter->setPen(pen);
//        painter->drawEllipse(rect);
//    }
//    else
//    {
//        QPen pen(Qt::black, 3);
//        painter->setPen(pen);
//        painter->drawRect(rect);
//    }
    painter->drawPicture(0, 0, m_picture);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}
