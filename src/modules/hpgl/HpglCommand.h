#ifndef HPGLCOMMAND_H
#define HPGLCOMMAND_H

#include <QtCore>

class HpglCommand
{
public:
    HpglCommand(const QString &name, const QString &arg);

    QString m_name;
    QVariant m_argument;
};

#endif // HPGLCOMMAND_H
