#include "HpglDocument.h"

//Data Data::Null;

HpglDocument::HpglDocument()
    //: SharedData<HpglDocumentPrivate>() // d(new HpglDocumentPrivate)
{
    d = new HpglDocumentPrivate;
}

HpglDocument::HpglDocument(std::nullptr_t null)
{
    Q_UNUSED(null)
}

HpglDocument::HpglDocument(const HpglDocument &other)
    : d(other.d)
{
}

//HpglDocument::HpglDocument(const QExplicitlySharedDataPointer<HpglDocumentPrivate> &p)
//    : d(p)
//{
//}

//HpglDocument::HpglDocument(const Data &null)
//{
//    Q_ASSERT(isNull());
//    Q_UNUSED(null)
//}

void test()
{
    HpglDocument d;
    HpglDocument d2 = nullptr;
    HpglDocument d3(nullptr);

}
