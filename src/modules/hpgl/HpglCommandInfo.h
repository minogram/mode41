#ifndef HPGLCOMMANDINFO_H
#define HPGLCOMMANDINFO_H

#include <QtCore>

class HpglCommandInfo
{
public:
    HpglCommandInfo();
    HpglCommandInfo(const HpglCommandInfo &other);
    HpglCommandInfo(const QString &name, const QString &param, const QString &description);

    const QString &name() const { return m_name; }
    const QString &param() const { return m_param; }
    const QString &description() const { return m_description; }

private:
    QString m_name;
    QString m_param;
    QString m_description;
};

Q_DECLARE_METATYPE(HpglCommandInfo)

#endif // HPGLCOMMANDINFO_H
