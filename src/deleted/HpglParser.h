#ifndef HPGLPARSER_H
#define HPGLPARSER_H

#include <QTextStream>
#include <QString>
#include <QRegularExpression>

class HpglParser
{
private:
    HpglParser();

public:
    static const QString &parseLine(const QString &data);
    static QList<QPointF> parsePoints(const QString &arg);

private:
    static QRegularExpression m_regex;
};

#endif // HPGLPARSER_H
