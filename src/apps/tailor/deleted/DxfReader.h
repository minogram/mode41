#ifndef DXFREADER_H
#define DXFREADER_H

#include <QTextStream>

namespace dxf
{

/**
 * @brief The DxfReader class
 */
class DxfReader
{
public:
    DxfReader();
    void setDevice(QIODevice *device);
    int code() { return m_code; }
    QString &value() { return m_value; }
    bool readNext();
    bool is(int code) { return m_code == code; }
    bool is(int code, const QString &value) { return (m_code == code) && (m_value == value); }
    bool isNot(int code) { return !is(code); }
    bool isNot(int code, const QString &value) { return !is(code, value); }
    bool skipTo(int code);
    bool skipTo(int code, const QString &value);
    int lineNumber() { return m_lineNumber; }

    bool readUntil(int code) { return readNext() && !is(code); }
    bool readUntil(int code, const QString &value) { return readNext() && !is(code, value); }
private:
    QTextStream in;
    int m_lineNumber = 0;
    int m_code = 0;
    QString m_value;
};

}
#endif // DXFREADER_H
