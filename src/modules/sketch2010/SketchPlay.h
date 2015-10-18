#ifndef MODE41_SKETCHPLAY_H
#define MODE41_SKETCHPLAY_H

#include "SketchDrawing.h"
//#include <QtCore>
//#include <QtGui>
#include <QPainter>

class SketchPlay
{
public:
    SketchPlay(SketchDrawing *drawing);
    void play(QPainter *painter);
private:
    void playGroup(SketchContainer *);
    void playPath(SketchPath *);
    void playLoop(SketchLoop *);
    void playSegment(SketchVertex *v1, SketchVertex *v2);
protected:
    SketchDrawing *m_drawing;
    QPainter *m_painter;
    QPainterPath m_path;
};

#endif // SKETCHPLAY_H
