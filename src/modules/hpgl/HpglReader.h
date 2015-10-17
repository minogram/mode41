#ifndef HPGLREADER_H
#define HPGLREADER_H

#include <QtCore>
#include "HpglReference.h"

class HpglDocument;
class HpglCommand;

class HpglReader
{
public:
    HpglReader();
    HpglDocument load(const QString &filePath);
    HpglReference &reference() { return m_reference; }

private:

private:
    HpglCommand parseCommand(const QString &src);
    QList<QPointF> parsePoints(const QString &arg);
    QList<int> parseInts(const QString &arg);
    QList<float> parseFloats(const QString &arg);
    QVariantList parseArgs(const QString &arg, const QString &format);

    const QSet<QString> &unknowns() { return m_unknowns; }
private:
    HpglReference m_reference;
    QSet<QString> m_unknowns;

private:
    static void initialize();
    static bool g_initialized;
    static QRegularExpression g_regex;
};

#endif // HPGLREADER_H
