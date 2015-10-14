#ifndef HPGLREADER_H
#define HPGLREADER_H

#include "HpglParser.h"
#include "HpglDocument.h"
#include <QSharedPointer>
#include <QTextStream>
#include <QtCore>

class HpglReader : public HpglParser
{
public:
    HpglReader();
    QSharedPointer<HpglDocument> load(const QString &fileName);

private:
    QSharedPointer<HpglDocument> m_doc;
    void parse(const QString &line);
    void parsePoints(const QString &data, QList<QPointF> &points);
};

#endif // HPGLREADER_H
