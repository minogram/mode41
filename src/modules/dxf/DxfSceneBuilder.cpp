#include "DxfSceneBuilder.h"
#include <QMap>
#include <QColor>
#include <QDebug>
#include <QSharedPointer>

using namespace dxf;

DxfSceneBuilder::DxfSceneBuilder()
{
}

//QColor getLayerColor(QString layer)
//{
//    if (layer == "") return Qt::black;
//    return Qt::black;
//}

//QPen *createPen(QString layer)
//{
//    QPen *pen = new QPen();
//    QColor color = getLayerColor(layer);
//    pen.setColor(color);
//    pen.setWidth(1);
//    pen.setCosmetic(true);
//    return pen;
//}

//QPen *getLayerPen(QString layer)
//{

//}

//enum AAMALayer
//{
//    Unknown = 0,
//    Cut = 1,            //!<< CUT, OUTLINE (Rotary Blade)
//    Notch = 4,          //!<< NOTCH
//    Draw = 8,           //!<< DRAW, INK (Marker tool)
//    Marker = 10,        //!<< MARKER
//    InternalCut = 11,   //!<< INTCUT
//    Drill = 13,         //!<< DRILL
//    TextAlt = 15,       //!<< TEXT (Annotations)
//    Text = 19,          //!<< TEXT (Marker)
//    Reference = 26,
//};

int DxfSceneBuilder::getLayerColor(QString layer)
{
    if (layer == "1") return Qt::red; // CUT
    if (layer == "6") return Qt::green;
    if (layer == "7") return Qt::magenta;
    if (layer == "11") return Qt::blue;
    qDebug() << "MISSING COLOR LAYER = " << layer;
    return Qt::cyan;
}

void DxfSceneBuilder::buildScene(dxf::DxfModel *model, QGraphicsScene *scene)
{
    scene->clear();

//    QPen pen;
//    pen.setColor(Qt::red);
//    pen.setWidth(1);
//    pen.setCosmetic(true);


    //QMap<QString, QPen *> pens;

    //QMap<QString, QColor> colors;
    //QSet<QString> layers;
    //QSet("11", "7", "1", "6")
    //QSet("1", "6", "11", "7")
    foreach (auto block, model->blocks)
    {
        foreach (auto entity, block->entities)
        {
            if (entity->type == dxf::EntityType::LINE)
            {
                auto line = qSharedPointerCast<DxfLine>(entity); // QSharedPointerstd::static_pointer_cast<dxf::DxfLine>(entity);

                //int color = getLayerColor(line->layer);
                QPen pen;
                pen.setColor(Qt::red); //color);
                pen.setWidth(1);
                pen.setCosmetic(true);

                //pen.setColor(color);

                scene->addLine(line->x1, line->y1, line->x2, line->y2, pen);
                continue;
            }
            else if (entity->type == dxf::EntityType::POLYLINE)
            {
                auto polyline = QSharedPointer<DxfPolyline>::create();
                auto first = polyline->vertices.first();
                QPainterPath path(QPointF(first->x, first->y));
                for (int i=1; i<polyline->vertices.size(); ++i) {
                    auto vertex = polyline->vertices.at(i);
                    path.lineTo(vertex->x, vertex->y);
                }
                if (polyline->isClosed()) path.closeSubpath();

//                int color = getLayerColor(polyline->layer);
//                pen.setColor(color);
               // int color = getLayerColor(polyline->layer);
                QPen pen;
                pen.setColor(Qt::blue);
                pen.setWidth(1);
                pen.setCosmetic(true);

                scene->addPath(path, pen);
                continue;
            }
        }
    }

    //qDebug() << layers;
}
