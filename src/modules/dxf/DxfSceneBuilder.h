#ifndef DXFSCENEBUILDER_H
#define DXFSCENEBUILDER_H

#include "DxfModel.h"
#include <QMap>
#include <QColor>
#include <QGraphicsScene>

class DxfSceneBuilder
{
public:
    DxfSceneBuilder();
    void buildScene(dxf::DxfModel *model, QGraphicsScene *scene);

private:
    int getLayerColor(QString layer);
};

#endif // DXFSCENEBUILDER_H
