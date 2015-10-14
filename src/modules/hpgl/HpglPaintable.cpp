#include "HpglPaintable.h"
#include <QtCore>
#include <QPainter>

HpglPaintable::HpglPaintable(const HpglDocument &hpgl)
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
    foreach (auto cmd, m_doc.items()) {
        auto name = cmd.name();
        auto argument = cmd.argument();

        if (name == "PU") {
            //painter->drawPath(*path);
        } else if (name == "PD") {
            auto points = qvariant_cast<QList<QPointF>>(argument);
            foreach (auto point, points) {
                path.lineTo(point);
            }
        } if (name == "PA") {
            auto points = qvariant_cast<QList<QPointF>>(argument);
            foreach (auto point, points) {
                path.lineTo(point);
            }
        } if (name == "PR") {
        }
    }

    painter->drawPath(path);
}

