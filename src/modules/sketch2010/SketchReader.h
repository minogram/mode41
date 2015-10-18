#ifndef MODE41_SKETCHREADER_H
#define MODE41_SKETCHREADER_H

#include "SketchDrawing.h"
#include <QDomDocument>

class SketchReader
{
public:
    SketchReader();
    SketchDrawing *load(const QString &filePath);
protected:
    SketchDrawing *readDrawing(const QDomElement &xdrawing);
    SketchElement *readElement(const QDomElement &xelem);
    SketchGroup *readGroup(const QDomElement &xgroup);
    SketchPath *readPath(const QDomElement &xpath);
    SketchLoop *readLoop(const QDomElement &xloop);
    SketchVertex *readVertex(const QDomElement &xvertex);
protected:
    QPointF readPointF(const QString &src);
    bool readBool(const QString &src);
    QColor readColor(const QString &src);
    QBrush readFill(const QString &src);
    QBrush readStroke(const QString &src);
};

#endif // SKETCHREADER_H
