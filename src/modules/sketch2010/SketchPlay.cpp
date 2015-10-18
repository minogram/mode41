#include "SketchPlay.h"
#include "SketchDrawing.h"
#include <QtCore>
#include <QtGui>

SketchPlay::SketchPlay(SketchDrawing *drawing)
    : m_drawing(drawing)
{
}

void SketchPlay::play(QPainter *painter)
{
    m_painter = painter;
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::red);
    pen.setCosmetic(true);
    painter->setPen(pen);

    playGroup(m_drawing);
    painter->drawPath(m_path);
    m_painter = nullptr;
}

void SketchPlay::playGroup(SketchContainer *container)
{
    foreach (auto elem, container->elements) {
        auto nodeType = elem->nodeType();
        if (nodeType == SketchNode::Drawing || nodeType == SketchNode::Group)
        {
            playGroup((SketchContainer *)elem);
        }
        else if (nodeType == SketchNode::Path)
        {
            playPath((SketchPath *)elem);
        }
    }
}

void SketchPlay::playPath(SketchPath *path)
{
    foreach (auto loop, path->loops) {
        playLoop(loop);
    }
}

void SketchPlay::playLoop(SketchLoop *loop)
{
    auto v1 = loop->vertices.first();
    m_path.moveTo(v1->location);

    for (int i=1; i<loop->vertices.size()-1; i++) {
        auto v2 = loop->vertices.at(i);
        playSegment(v1, v2);
        v1 = v2;
    }
    if (loop->isClosed) {
        auto v2 = loop->vertices.at(0);
        playSegment(v1, v2);
        m_path.closeSubpath();
    }
}

void SketchPlay::playSegment(SketchVertex *v1, SketchVertex *v2)
{
    Q_ASSERT(v1 != v2);

    if (v1->nextVector.isNull() && v2->prevVector.isNull()) {
        m_path.lineTo(v2->location);
    }
    else {
        m_path.lineTo(v1->location + v1->nextVector);
        m_path.lineTo(v2->location);
        m_path.lineTo(v2->location + v2->prevVector);
    }
}
