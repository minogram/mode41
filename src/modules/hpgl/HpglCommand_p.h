#ifndef HPGLCOMMAND_D_H
#define HPGLCOMMAND_D_H

#include <QtCore>

class HpglCommandPrivate : public QSharedData
{
    friend class HpglCommand;
    HpglCommandPrivate() { }
    HpglCommandPrivate(const QString &name, const QVariantList &args)
        : m_name(name), m_args(args) { }

    QString m_name;
    QVariant m_arg;
    QVariantList m_args;
};

Q_DECLARE_METATYPE(QPointF)
Q_DECLARE_METATYPE(QList<QPointF>)

#endif // HPGLCOMMAND_D_H

