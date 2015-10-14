#ifndef HPGLTEXTREADER_H
#define HPGLTEXTREADER_H

#include <QtCore>
#include "Hpgl.h"
//#include "HpglDocument.h"

class HpglTextReader
{
public:
    HpglTextReader();
    QSharedPointer<HpglDocument> load(const QString &filePath);
//    void doLine(const QString &line);
    void doCmd(const QString &cmd);
signals:

public slots:

private:
    QTextStream in;
    QRegularExpression m_regex;
    QSharedPointer<HpglDocument> m_doc;
};

#endif // HPGLTEXTREADER_H
