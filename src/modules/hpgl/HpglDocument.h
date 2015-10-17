#ifndef HPGLDOCUMENT_H
#define HPGLDOCUMENT_H

#include <QtCore>
#include "HpglDocument_p.h"
#include "HpglCommand.h"

//template <typename T>
//class Shared
//{
//    Shared() { d = new T(); }
//    Shared(std::nullptr_t null) { }
//    bool isNull() { return d.data() == nullptr; }
//protected:
//    QExplicitlySharedDataPointer<T> d;
//};

//#define DECLARE_SHARED(T) \
//public: \
//    T(std::nullptr_t null) {} \
//    T() : d(new T)
//#endif

///
/// \brief The HpglDocument class
///
/// class Something
/// - define Something()
/// - define Something(const Something &)
/// - define isNull()
/// - has only one QExplicitlySharedDataPointer<SomethingPrivate> d;
/// - define all member methods here
///
/// class SomethingPrivate : public QSharedData
/// - define all member variables here
///
class HpglDocument
{
public:
    HpglDocument(std::nullptr_t null);
    HpglDocument();
    HpglDocument(const HpglDocument &other);
    bool isNull() { return d.data() == nullptr; }

    QList<HpglCommand> &items() { return d->items; }
protected:
    QExplicitlySharedDataPointer<HpglDocumentPrivate> d;
};

Q_DECLARE_METATYPE(HpglDocument)

#endif // HPGLDOCUMENT_H

