#ifndef HPGLSTATE_H
#define HPGLSTATE_H

#include <QtCore>

class HpglState
{
public:
    HpglState();
    void reset();

    bool selectPen(int penNumber); // { m_penNumber = penNumber; }
    bool penUp(); // { m_penDown = false; }
    bool penDown(); // { m_penDown = true; }
    bool moveAbs(const QPointF &point);
//{
//        m_penPos = absolute;
//    }
    bool moveRel(const QPointF &point);
//{
//        m_penPos += relative;
//    }

    const QPointF &penPos() const { return m_penPos; }
    int penNumber() const { return m_penNumber; }
    bool isPenDown() const { return m_penDown; }

private:
    bool m_penDown;
    int m_penNumber;
public:
    int m_speed;
public:
    QPointF m_penPos;
};

#endif // HPGLSTATE_H
