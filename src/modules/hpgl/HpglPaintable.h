#ifndef HPGLPAINTABLE_H
#define HPGLPAINTABLE_H

#include <QPainter>
#include "HpglDocument.h"

class HpglPaintable
{
public:
    HpglPaintable(HpglDocument *hpgl);
    void paint(QPainter *painter);

signals:

public slots:

private:
    HpglDocument *m_doc;
};

#endif // HPGLPAINTABLE_H
