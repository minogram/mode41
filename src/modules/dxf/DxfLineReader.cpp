#include "DxfLineReader.h"

DxfLineReader::DxfLineReader()
{
}

void DxfLineReader::setDevice(QIODevice *device)
{
    in.setDevice(device);
}

bool DxfLineReader::atEnd()
{
    if (m_peekNext) return false;
    return in.atEnd();
}

void DxfLineReader::skip()
{
    while (readNoZero()) {}
}

bool DxfLineReader::moveNext()
{
    if (m_peekNext)
    {
        m_code = m_codeNext;
        m_value = m_valueNext;
        m_peekNext = false;
        return true;
    }
    else if (in.atEnd())
    {
        return false;
    }
    else
    {
        m_code = in.readLine().trimmed().toInt();
        m_value = in.readLine().trimmed().toInt();
        m_peekNext = false;
        return true;
    }
}

bool DxfLineReader::peekNext()
{
    if (m_peekNext)
    {
        return true;
    }
    else if (in.atEnd())
    {
        return false;
    }
    else
    {
        m_codeNext = in.readLine().trimmed().toInt();
        m_valueNext = in.readLine().trimmed();
        m_peekNext = true;
        return true;
    }
}

bool DxfLineReader::readZero()
{
    if (peekNext())
    {
        if (m_codeNext == 0)
        {
            moveNext();
            return true;
        }
    }
    return false;
}

bool DxfLineReader::readNoZero()
{
    if (peekNext())
    {
        if (m_codeNext != 0)
        {
            moveNext();
            return true;
        }
    }
    return false;
}
