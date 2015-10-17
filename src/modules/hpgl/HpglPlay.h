#ifndef HPGLPAINTABLE_H
#define HPGLPAINTABLE_H

#include <QtCore>
#include <QPainter>
#include "HpglDocument.h"
#include "HpglState.h"

class HpglPlay
{
public:
    HpglPlay(HpglDocument doc);
private:
    void initPens();
protected:
    void play();
    QPen pen(int number) const;
public:
    //virtual void setPen(int penNumber = 0) = 0;
    virtual void addPath(const QPainterPath &path, const QPen &pen) = 0;
private:
    void reset();
    void addPath();

    QPen m_penDefault;
    QMap<int, QPen> m_pens;

    HpglDocument m_doc;
    HpglState m_state;
    QPainterPath m_path;
};

#endif // HPGLPAINTABLE_H
