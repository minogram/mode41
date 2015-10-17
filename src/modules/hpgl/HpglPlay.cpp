#include <QtCore>
#include <QPainter>
#include "HpglPlay.h"
#include "HpglCommand.h"
#include "HpglDocument.h"
#include "HpglState.h"

HpglPlay::HpglPlay(HpglDocument doc)
    : m_doc(doc)
{
    initPens();
}

void HpglPlay::initPens()
{
    int penWidth = 2;
    QColor penColors[] = {
        Qt::gray, Qt::black,
        Qt::red, Qt::green, Qt::blue,
        Qt::cyan, Qt::magenta, Qt::yellow,
    };

    m_penDefault.setColor(Qt::lightGray);
    m_penDefault.setWidth(penWidth);
    m_penDefault.setCosmetic(true);

    for (int i=0; i<8; i++) {
        QPen pen;
        pen.setColor(penColors[i]);
        pen.setWidth(2);
        pen.setCosmetic(true);
        m_pens.insert(i, pen);
    }
}

QPen HpglPlay::pen(int number) const
{
    return m_pens.value(number, m_penDefault);
}

void HpglPlay::play()
{
    reset();

    foreach (auto cmd, m_doc.items()) {
        auto name = cmd.name();

        if (name == "SP") {
            auto penNumber = cmd.args().at(0).toInt();
            if (m_state.selectPen(penNumber)) {
                addPath();
            }
        }
        else if (name == "PU") {
            auto &points = cmd.args();
            if (m_state.penUp()) {
            }
            if (points.count() > 0) {
                m_state.moveAbs(points.last().value<QPointF>());
                m_path.moveTo(m_state.penPos());
            }
        }
        else if (name == "PD") {
            auto &points = cmd.args();
            if (m_state.penDown()) {
                // addPath();
            }
            if (points.count() > 0) {
                foreach (auto point, points) {
                    m_state.moveAbs(point.value<QPointF>());
                    m_path.lineTo(m_state.penPos());
                }
            }
        }
        else if (name == "PA") {
            auto &points = cmd.args();

            if (points.count() > 0) {
                foreach (auto point, points) {
                    m_state.moveAbs(point.value<QPointF>());
                    if (m_state.isPenDown())
                        m_path.lineTo(m_state.penPos());
                    else
                        m_path.moveTo(m_state.penPos());
                }
            }
        }
        else if (name == "PR") {
            auto &points = cmd.args();
            if (points.count() > 0) {
                foreach (auto point, points) {
                    m_state.moveRel(point.value<QPointF>());
                    if (m_state.isPenDown())
                        m_path.lineTo(m_state.penPos());
                    else
                        m_path.moveTo(m_state.penPos());
                }
            }
        }
        else if (name == "CI") {
            auto radius = cmd.args().at(0).toFloat();
            m_path.addEllipse(m_state.penPos(), radius, radius);
        }
        else if (name == "IN") {
            // initialize
            m_state.penUp();
            m_state.selectPen(0);
            m_state.moveAbs(QPoint(0, 0));
        }
        else if (name == "DF") {
            // default
        }
    }
    addPath();
}

void HpglPlay::reset()
{
    m_state.reset();
    m_path = QPainterPath();
    m_path.moveTo(m_state.penPos());
}

void HpglPlay::addPath()
{
    if (!m_path.isEmpty()) {
        //setPen(m_state.penNumber());
        auto pen = this->pen(m_state.penNumber());
//        if (m_painter->pen() != pen) {
//            m_painter->setPen(pen);
//        }

        addPath(m_path, pen);
        // make new path and move to current position
        m_path = QPainterPath();
        m_path.moveTo(m_state.penPos());
    }
}

//void HpglPlay::setPen(int penNumber)
//{
////    auto pen = this->pen(penNumber);
////    if (m_painter->pen() != pen) {
////        m_painter->setPen(pen);
////    }
//}

//void HpglPlay::addPath(const QPainterPath &path)
//{
////    m_painter->drawPath(path);
//}
