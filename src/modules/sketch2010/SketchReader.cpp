#include "SketchReader.h"
#include <QtCore>
#include <QtXml>
#include <QDomDocument>
#include <QColor>

SketchReader::SketchReader()
{
}

SketchDrawing *SketchReader::load(const QString &filePath)
{
    QDomDocument doc("sketch2010");
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly))
        return nullptr;

    if (!doc.setContent(&file)) {
        file.close();
        return nullptr;
    }

    auto drawing = readDrawing(doc.documentElement());
    file.close();
    return drawing;
}

SketchDrawing *SketchReader::readDrawing(const QDomElement &xdrawing)
{
    auto drawing = new SketchDrawing();
    for (int i=0; i<xdrawing.childNodes().length(); i++) {
        auto xchild = xdrawing.childNodes().at(i).toElement();
        if (xchild.isNull()) continue;
        auto child = readElement(xchild);
        if (child == nullptr) continue;
        drawing->elements.append(child);
    }
    return drawing;
}

SketchElement *SketchReader::readElement(const QDomElement &xelem)
{
    auto name = xelem.nodeName();
    if (name == "SketchGroup") {
        return readGroup(xelem);
    }
    else if (name == "SketchPath") {
        return readPath(xelem);
    }
    else
    {
        //qDebug() << "ignore: " << name;
    }
    return nullptr;
}

SketchGroup *SketchReader::readGroup(const QDomElement &xgroup)
{
    auto group = new SketchGroup();
    for (int i=0; i<xgroup.childNodes().length(); i++) {
        auto xchild = xgroup.childNodes().at(i).toElement();
        if (xchild.isNull()) continue;
        auto child = readElement(xchild);
        if (child)
            group->elements.append(child);
    }
    return group;
}

SketchPath *SketchReader::readPath(const QDomElement &xpath)
{
    auto path = new SketchPath();
    for (int i=0; i<xpath.childNodes().length(); i++) {
        auto xloop = xpath.childNodes().at(i).toElement();
        if (xloop.isNull()) continue;
        auto loop = readLoop(xloop);
        if (loop)
            path->loops.append(loop);
    }
    return path;
}

SketchLoop *SketchReader::readLoop(const QDomElement &xloop)
{
    auto loop = new SketchLoop();
    loop->isClosed = readBool(xloop.attribute("IsClosed"));
    loop->fill = readColor(xloop.attribute("Fill"));
    loop->stroke = readStroke(xloop.attribute("Stroke"));
    loop->strokeThickness = xloop.attribute("StrokeThickness").toFloat();
    for (int i=0; i<xloop.childNodes().length(); i++) {
        auto xvertex = xloop.childNodes().at(i).toElement();
        if (xvertex.isNull()) continue;
        auto vertex = readVertex(xvertex);
        if (vertex)
            loop->vertices.append(vertex);
    }
    return loop;
}

//Location="497.38674591784,161.584090737017" PreviousVector="4,-14.5" NextVector="-4,14.5" Connectivity="Symmetric"
SketchVertex *SketchReader::readVertex(const QDomElement &xvertex)
{
    auto vertex = new SketchVertex();
    vertex->location =readPointF(xvertex.attribute("Location"));
    vertex->prevVector = readPointF(xvertex.attribute("PreviousVector"));
    vertex->nextVector = readPointF(xvertex.attribute("NextVector"));
    return vertex;
}

QPointF SketchReader::readPointF(const QString &src)
{
    QPointF point;
    auto tokens = src.split(',');
    point.setX(tokens.at(0).toFloat());
    point.setY(tokens.at(1).toFloat());
    return point;
}

bool SketchReader::readBool(const QString &src)
{
    if (src == "True") return true;
    return false;
}

QColor SketchReader::readColor(const QString &src)
{
    QColor color(src);
    return color;
}

QBrush SketchReader::readFill(const QString &src)
{
    if (src == "{x:Null}") return QBrush();
    QColor color = readColor(src);
    QBrush brush(color);
    return brush;
}

QBrush SketchReader::readStroke(const QString &src)
{
    if (src == "{x:Null}") return QBrush();
    QColor color = readColor(src);
    QBrush brush(color);
    return brush;
}
