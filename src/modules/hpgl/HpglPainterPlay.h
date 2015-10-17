#ifndef HPGLPAINTERPLAY_H
#define HPGLPAINTERPLAY_H

#include <QtCore>
#include <QPainter>
#include <QGraphicsScene>
#include "HpglDocument.h"
#include "HpglPlay.h"

class HpglPainterPlay : public HpglPlay
{
public:
    HpglPainterPlay(HpglDocument doc) : HpglPlay(doc) { }
    void play(QPainter *painter);
protected:
    //void setPen(int penNumber = 0) Q_DECL_OVERRIDE;
    void addPath(const QPainterPath &path, const QPen &pen) Q_DECL_OVERRIDE;

protected:
    QPainter *m_painter;
};

class HpglScenePlay : public HpglPlay
{
public:
    HpglScenePlay(HpglDocument doc) : HpglPlay(doc) { }
    void play(QGraphicsScene *scene);
protected:
    //void setPen(int penNumber = 0) Q_DECL_OVERRIDE;
    void addPath(const QPainterPath &path, const QPen &pen) Q_DECL_OVERRIDE;

protected:
    QGraphicsScene *m_scene;
};

#endif // HPGLPAINTERPLAY_H
