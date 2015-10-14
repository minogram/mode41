#ifndef HPGLTEXTREADER_H
#define HPGLTEXTREADER_H

#include "HpglDocument.h"
#include <QTextStream>
#include <QRegularExpression>

class HpglTextReader
{
public:
    HpglTextReader();
    HpglDocument load(const QString &filePath);
    static QList<QPointF> parsePoints(const QString &arg);

private:
    QRegularExpression m_regex;
};

#endif // HPGLTEXTREADER_H
