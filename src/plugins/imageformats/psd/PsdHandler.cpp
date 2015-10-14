#include "PsdHandler.h"
#include "FreeImage.h"
#include "QFreeImage.h"

#include <QVariant>
#include <QDebug>
#include <QImage>
#include <QtGlobal>
#include <QColor>
#include <QIODevice>
#include <QDataStream>

// RAII WRAPPER FOR DIBS ////////////////////////////////////////////////
class ScopedDib
{
private:
    FIBITMAP *m_dib;

    ScopedDib(const ScopedDib&);
    ScopedDib& operator=(const ScopedDib&);
public:
    explicit ScopedDib(FIBITMAP *dib)
        : m_dib(dib)
    {
    }
    ~ScopedDib()
    {
        if (m_dib)
        {
            FreeImage_Unload(m_dib);
            m_dib = 0;
        }
    }
    FIBITMAP *get() const
    {
        return m_dib;
    }

    void reset(FIBITMAP *p = 0)
    {
        Q_ASSERT(p == 0 || p != m_dib);
        ScopedDib(p).swap(*this);
    }

    void swap(ScopedDib &rhs)
    {
        FIBITMAP *temp = rhs.m_dib;
        rhs.m_dib = m_dib;
        m_dib = temp;
    }

    // implicit conversion to bool a-la boost
    typedef FIBITMAP *ScopedDib::*uncpecified_bool_type;
    operator uncpecified_bool_type() const
    {
        return (m_dib == NULL)? NULL : &ScopedDib::m_dib;
    }
    bool operator!() const
    {
        return m_dib == NULL;
    }

};
// FREEIMAGE IO PROCS /////////////////////////////////////////////////

PsdHandler::PsdHandler()
    : QImageIOHandler()
{
}

bool PsdHandler::canRead() const
{
    if (!device()->isReadable())
        return false;

    FREE_IMAGE_FORMAT fif = QFreeImage::GetFIF(device(), format());
    return FreeImage_FIFSupportsReading(fif);

//    if (d->tiff)
//        return true;
//    if (QTiffHandlerPrivate::canRead(device())) {
//        setFormat("tiff");
//        return true;
//    }
}

//bool XxxHandler::canRead(QIODevice *device)
//{
//    return QTiffHandlerPrivate::canRead(device);
//}

bool PsdHandler::read(QImage *image)
{
    FREE_IMAGE_FORMAT fif = QFreeImage::GetFIF(device(),format());

    if (!FreeImage_FIFSupportsReading(fif))
        return false;

    ScopedDib dib(0);

    // HACK: FreeImage(at least ver. 3.13.1) can not load FIF_PSD
    // from stream. We load it from memory.
    if (fif == FIF_PSD)
    {
        QByteArray mem = device()->readAll();
        if (mem.isEmpty())
            return false;
        FIMEMORY *fmem = FreeImage_OpenMemory((BYTE*)mem.data(), mem.size());
        if (!fmem)
            return false;
        dib.reset(FreeImage_LoadFromMemory(FIF_PSD,fmem));
        FreeImage_CloseMemory(fmem);
    }
    else
    {
        dib.reset(FreeImage_LoadFromHandle(fif, &QFreeImage::fiio(),(fi_handle)device()));
    }

    if (!dib)
        return false;

    QImage result = QFreeImage::FIBitmapToQImage(dib.get());

    if (QFreeImage::IsQImageNone(result))
        return false;

    // set resolution
    result.setDotsPerMeterX(FreeImage_GetDotsPerMeterX(dib.get()));
    result.setDotsPerMeterY(FreeImage_GetDotsPerMeterY(dib.get()));

    // set palette
    if (FreeImage_GetPalette(dib.get()) != NULL)
    {
        QVector<QRgb> pal = QFreeImage::GetPalette(dib.get());
        if (!QFreeImage::IsPaletteNone(pal))
            result.setColorTable(pal);
    }

    *image = result;
    return true;
}

//bool XxxHandler::write(const QImage &image)
//{
//    if (!device()->isWritable())
//        return false;
//    return true;
//}

QByteArray PsdHandler::name() const
{
    return "xxx";
}

QVariant PsdHandler::option(ImageOption option) const
{
        return QVariant();
        Q_UNUSED(option);
//    if (option == Size && canRead()) {
//        if (d->readHeaders(device()))
//            return d->size;
//    } else if (option == CompressionRatio) {
//        return d->compression;
//    } else if (option == ImageFormat) {
//        if (d->readHeaders(device()))
//            return d->format;
//    } else if (option == ImageTransformation) {
//        if (d->readHeaders(device()))
//            return int(d->transformation);
//    }
//    return QVariant();
}

void PsdHandler::setOption(ImageOption option, const QVariant &value)
{
    Q_UNUSED(option);
    Q_UNUSED(value);
//    if (option == CompressionRatio && value.type() == QVariant::Int)
//        d->compression = value.toInt();
//    if (option == ImageTransformation) {
//        int transformation = value.toInt();
//        if (transformation > 0 && transformation < 8)
//            d->transformation = QImageIOHandler::Transformations(transformation);
//    }
}

bool PsdHandler::supportsOption(ImageOption option) const
{
    Q_UNUSED(option);
    return false;
//    return option == CompressionRatio
//            || option == Size
//            || option == ImageFormat
//            || option == ImageTransformation
//            || option == TransformedByDefault;
}

