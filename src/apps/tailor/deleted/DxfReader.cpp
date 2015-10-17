#include "DxfReader.h"
#include <QString>

dxf::DxfReader::DxfReader()
{
}

void dxf::DxfReader::setDevice(QIODevice *device)
{
    in.setDevice(device);
}

bool dxf::DxfReader::readNext(void)
{
    if (in.atEnd()) return false;
    QString line1 = in.readLine().trimmed();
    m_lineNumber++;

    if (in.atEnd()) return false;
    QString line2 = in.readLine().trimmed();
    m_lineNumber++;

    m_code = line1.toInt();
    m_value = line2;

    return true;
}

bool dxf::DxfReader::skipTo(int code)
{
    for (;;) {
        if (!readNext()) return false;
        if (is(code)) break;
    }
    return true;
}

bool dxf::DxfReader::skipTo(int code, const QString &value)
{
    for (;;) {
        if (!readNext()) return false;
        if (is(code, value)) break;
    }
    return true;
}
