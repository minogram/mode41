#ifndef HPGLTEXTREADER_H
#define HPGLTEXTREADER_H

#include <QTextStream>

class HpglTextReader
{
public:
    HpglTextReader();
    void load(const QString &filePath);
    void addLine(const QString &line);
signals:

public slots:

private:
    QTextStream in;
};

#endif // HPGLTEXTREADER_H
