#ifndef HPGLDOCUMENT_H
#define HPGLDOCUMENT_H

#include <QtCore>
#include "HpglCommand.h"

class HpglDocumentData;

class HpglDocumentData : public QSharedData
{
public:
    HpglDocumentData() {}
    HpglDocumentData(const HpglDocumentData &other)
        : QSharedData(other)
        , items(other.items) {}
    ~HpglDocumentData() {}

    QList<HpglCommand> items;
};

class HpglDocument
{
public:
    HpglDocument() { d = new HpglDocumentData; }
    HpglDocument(const HpglDocument &other)
        : d(other.d) {}

    // todo: QList<HpglCommand> items() - this not work, strange...
    QList<HpglCommand> &items() const { return d->items; }
private:
    //QList<HpglCommand> m_items;
    //QSharedDataPointer<HpglDocumentData> d;
    QExplicitlySharedDataPointer<HpglDocumentData> d;
};

//Q_PRIMITIVE_TYPE specifies that Type is a POD (plain old data) type with no constructor or destructor, or else a type where every bit pattern is a valid object and memcpy() creates a valid independent copy of the object.
//Q_MOVABLE_TYPE specifies that Type has a constructor and/or a destructor but can be moved in memory using memcpy().
//Q_COMPLEX_TYPE (the default) specifies that Type has constructors and/or a destructor and that it may not be moved in memory."
//Q_DECLARE_TYPEINFO(HpglDocument, Q_COMPLEX_TYPE);

#endif // HPGLDOCUMENT_H

