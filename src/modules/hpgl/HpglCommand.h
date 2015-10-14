#ifndef HPGLCOMMAND_H
#define HPGLCOMMAND_H

#include <QtCore>

class HpglCommand
{
public:
    HpglCommand(const QString &name, const QString &arg);

    const QString &name() const { return m_name; }
    QVariant argument() const { return m_argument; }
private:
    QString m_name;
    QVariant m_argument;
};

//Q_DECLARE_TYPEINFO(HpglCommand, Q_)
//Q_DECLARE_TYPEINFO(HpglCommand, ;
//Q_DECLARE_TYPEINFO(HpglCommand, Q_COMPLEX_TYPE);

#endif // HPGLCOMMAND_H
