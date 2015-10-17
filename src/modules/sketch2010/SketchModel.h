#ifndef SKETCHMODEL_H
#define SKETCHMODEL_H

#include <QtCore>
#include <QDomDocument>

class SketchModel
{
public:
    SketchModel();
    void load(const QString &filePath);
    QDomDocument m_dom;
    void readDrawing();
signals:

public slots:
};

class SketchDrawing
{
public:
    QSizeF m_size;
};

class SketchPath
{
};

class SketchLoop
{
};

class SketchNode
{
};

class SketchGroup
{
};

class SketchElement
{
};

#endif // SKETCHMODEL_H
