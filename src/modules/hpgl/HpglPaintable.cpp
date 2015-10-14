#include "HpglPaintable.h"
#include <QtCore>
#include <QPainter>

HpglPaintable::HpglPaintable(HpglDocument *hpgl)
    : m_doc(hpgl)
{
}

void HpglPaintable::paint(QPainter *painter)
{
    QPen pen;
    pen.setColor(Qt::blue);
    pen.setWidth(2);
    pen.setCosmetic(true);
    painter->setPen(pen);

    QPointF currPos;
    QPainterPath path;
    foreach (auto cmd, m_doc->items) {
        if (cmd.m_name == "PU") {
            //painter->drawPath(*path);
        } else if (cmd.m_name == "PD") {
            auto points = qvariant_cast<QList<QPointF>>(cmd.m_argument);
            foreach (auto point, points) {
                path.lineTo(point);
            }
        } if (cmd.m_name == "PA") {
            auto points = qvariant_cast<QList<QPointF>>(cmd.m_argument);
            foreach (auto point, points) {
                path.lineTo(point);
            }
        } if (cmd.m_name == "PR") {
        }
    }

    painter->drawPath(path);
}

