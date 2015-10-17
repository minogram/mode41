#include "HpglPainterPlay.h"
#include "HpglPlay.h"
#include <QtCore>

void HpglPainterPlay::play(QPainter *painter)
{
    m_painter = painter;
    HpglPlay::play();
    m_painter = nullptr;
}

//void HpglPainterPlay::setPen(int penNumber)
//{
//    auto pen = this->pen(penNumber);
//    if (m_painter->pen() != pen) {
//        m_painter->setPen(pen);
//    }
//}

void HpglPainterPlay::addPath(const QPainterPath &path, const QPen &pen)
{
    if (m_painter->pen() != pen) {
        m_painter->setPen(pen);
    }
    m_painter->drawPath(path);
}

// ========
void HpglScenePlay::play(QGraphicsScene *scene)
{
    m_scene = scene;
    HpglPlay::play();
    m_scene = nullptr;
}

//void HpglScenePlay::setPen(int penNumber)
//{
//    auto pen = this->pen(penNumber);
//    if (m_painter->pen() != pen) {
//        m_painter->setPen(pen);
//    }
//}

void HpglScenePlay::addPath(const QPainterPath &path, const QPen &pen)
{
    m_scene->addPath(path, pen);
}
