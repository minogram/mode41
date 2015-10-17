#ifndef HPGLREFERENCE_H
#define HPGLREFERENCE_H

#include <QtCore>
#include "HpglCommandInfo.h"

class HpglReference
{
public:
    HpglReference();

    void reset();
    void add(const QString &name, const QString &param, const QString &desc);
    void ignore(const QString &name);
    void build0(); // for yuka

    bool canIgnore(const QString &name);
    bool hasInfo(const QString &name);
    const QString &param(const QString &name);
private:
    QHash<QString, HpglCommandInfo> m_known;
    QSet<QString> m_ignore;
};

#endif // HPGLREFERENCE_H
