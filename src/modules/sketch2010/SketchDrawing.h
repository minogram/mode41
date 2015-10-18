#ifndef MODE41_SKETCHDRAWING_H
#define MODE41_SKETCHDRAWING_H

//#include <QtCore>
#include <QSizeF>
#include <QPointF>
#include <QLIST>
#include <QBrush>

class SketchNode;
class SketchElement;
class SketchContainer;
class SketchGroup;
class SketchDrawing;
class SketchPath;
class SketchLoop;
class SketchVertex;

class SketchNode
{
public:
    enum NodeType {
        Unknown = 0,
        Drawing,
        Path,
        Group,
        Loop,
        Vertex,
    };

    SketchNode(NodeType nodeType) { m_nodeType = nodeType; }
    virtual ~SketchNode() { }
    NodeType nodeType() { return m_nodeType; }
private:
    NodeType m_nodeType;
};

class SketchElement : public SketchNode
{
public:
    SketchElement(NodeType nodeType) : SketchNode(nodeType) { }
    virtual ~SketchElement() { }
    SketchContainer *parent = nullptr;
};

class SketchContainer : public SketchElement
{
public:
    SketchContainer(NodeType nodeType) : SketchElement(nodeType) { }
    virtual ~SketchContainer() {
        foreach (auto elem, elements) delete elem;
    }
    QList<SketchElement *> elements;
};

class SketchGroup : public SketchContainer
{
public:
    SketchGroup() : SketchContainer(NodeType::Group) { }
};

class SketchDrawing : public SketchContainer
{
public:
    SketchDrawing() : SketchContainer(NodeType::Drawing) { }
    QSizeF pageSize;
};

class SketchPath : public SketchElement
{
public:
    SketchPath() : SketchElement(NodeType::Path) { }
    ~SketchPath() { foreach (auto loop, loops) delete loop; }
    QList<SketchLoop *> loops;
};

class SketchLoop : public SketchNode
{
public:
    SketchLoop() : SketchNode(NodeType::Loop) { }
    ~SketchLoop() { foreach (auto vertex, vertices) delete vertex; }
    QList<SketchVertex *> vertices;
    bool isClosed = false;
    QBrush fill;
    QBrush stroke;
    float strokeThickness;
};

class SketchVertex : public SketchNode
{
public:
    SketchVertex() : SketchNode(NodeType::Vertex) { }
    QPointF location;
    QPointF prevVector;
    QPointF nextVector;
};

#endif // SKETCHDRAWING_H
