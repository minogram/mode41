#ifndef PTNSCENEBUILDER_H
#define PTNSCENEBUILDER_H

#include "PtnModel.h"
#include <QMap>
#include <QColor>
#include <QGraphicsScene>
#include <QSharedPointer>

class PtnSceneBuilder
{
public:
    PtnSceneBuilder();

    void buildScene(QSharedPointer<PtnDesign> design, QGraphicsScene *scene);
};

#endif // PTNSCENEBUILDER_H
