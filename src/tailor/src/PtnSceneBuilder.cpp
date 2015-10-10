#include "PtnSceneBuilder.h"
#include <QMap>
#include <QColor>
#include <QDebug>
#include <QSharedPointer>

PtnSceneBuilder::PtnSceneBuilder()
{
}

void PtnSceneBuilder::buildScene(QSharedPointer<PtnDesign> design, QGraphicsScene *scene)
{
    scene->clear();

    foreach (auto piece, design->pieces)
    {
        foreach (auto entity, piece->entities)
        {
            if (entity->type == PtnEntityType::Line)
            {
                auto line = entity.staticCast<PtnLine>();

                QPen pen;
                //pen.setColor(Qt::red);
                pen.setColor(QColor(254,23,99));
                pen.setWidth(2);
                pen.setCosmetic(true);
                scene->addLine(line->x1, line->y1, line->x2, line->y2, pen);
            }
            else if (entity->type == PtnEntityType::Polyline)
            {
                auto polyline = entity.staticCast<PtnPolyline>();
                auto first = polyline->vertices.first();
                QPainterPath path(QPointF(first->x, first->y));
                for (int i=1; i<polyline->vertices.size(); ++i) {
                    auto vertex = polyline->vertices.at(i);
                    path.lineTo(vertex->x, vertex->y);
                }
                if (polyline->isClosed()) path.closeSubpath();

                QPen pen;
//                pen.setColor(Qt::blue);
//                pen.setColor(QColor(220,220,50));
                pen.setColor(QColor(200,200,200));
                pen.setWidth(2);
                pen.setCosmetic(true);
                scene->addPath(path, pen);
            }
        }
    }
}
