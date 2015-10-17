#include "HpglState.h"

HpglState::HpglState()
{
    reset();
}

void HpglState::reset()
{
    m_penDown = false;
    m_penNumber = 0;
    m_penPos = QPointF(0, 0);
}

bool HpglState::selectPen(int penNumber)
{
    if (m_penNumber == penNumber) return false;
    m_penNumber = penNumber;
    return true;
}

bool HpglState::penUp()
{
    if (!m_penDown) return false;
    m_penDown = false;
    return true;
}

bool HpglState::penDown()
{
    if (m_penDown) return false;
    m_penDown = true;
    return true;
}

bool HpglState::moveAbs(const QPointF &point)
{
    if (m_penPos == point) return false;
    m_penPos = point;
    return true;
}

bool HpglState::moveRel(const QPointF &point)
{
    if (point.x() == 0 && point.y() == 0) return false;
    m_penPos += point;
    return true;
}
