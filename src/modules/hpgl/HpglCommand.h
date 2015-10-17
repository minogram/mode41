#ifndef HPGLCOMMAND_H
#define HPGLCOMMAND_H

#include <QtCore>
#include <HpglCommand_p.h>

//=================== macro for shared data reference
//#define DECLARE_SHARED(TYPE, PRIVATE) \
//    public: \
//        TYPE (std::nullptr_t) { } \
//        TYPE () : d(new PRIVATE ) {} \
//        TYPE (const TYPE &other) : d(other.d) {} \
//        bool isNull() { return d.data() == nullptr; } \
//    protected: \
//        QExplicitlySharedDataPointer<PRIVATE> d; \
//    private:

///
/// \brief The HpglCommand class
///
/// HpglCommand cmd1;
/// auto cmd2 = cmd1;
///
class HpglCommand
{
public:
    HpglCommand(std::nullptr_t) {}
    HpglCommand() : d(new HpglCommandPrivate) {}
    HpglCommand(const HpglCommand &other) : d(other.d) {}
    bool isNull() { return d.data() == nullptr; }
protected:
    QExplicitlySharedDataPointer<HpglCommandPrivate> d;

public:
    HpglCommand(const QString &name);
    HpglCommand(const QString &name, const QVariantList &args)
        : HpglCommand()
    {
        d->m_name = name;
        d->m_args = args;
    }
    const QString &name() const { return d->m_name; }
    const QVariantList &args() { return d->m_args; }
};

Q_DECLARE_METATYPE(HpglCommand)

#endif // HPGLCOMMAND_H
