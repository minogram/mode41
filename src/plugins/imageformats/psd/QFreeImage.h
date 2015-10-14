#ifndef FREEIMAGE2QIMAGE_H
#define FREEIMAGE2QIMAGE_H

#include <QImage>
#include "Freeimage.h"

///
/// \brief Qt FreeImage Utils
///
/// original source is
/// https://github.com/zoon/FreeImage-Plugin-for-QT4
///
class QFreeImage
{
private:
    QFreeImage() {}

public:
    static QImage load(const QString &filePath);

public:
    static QImage& QImageNone();
    static bool IsQImageNone(const QImage& qi);
    static QVector<QRgb>& PaletteNone();
    static bool IsPaletteNone(const QVector<QRgb> &pal);
    static QVector<QRgb> GetPalette(FIBITMAP *dib);
    static QImage FIBitmapToQImage(FIBITMAP *dib);

public:
    static FreeImageIO &fiio();
    static FREE_IMAGE_FORMAT GetFIF(QIODevice *device, const QByteArray& fmt);
};

#endif // FREEIMAGE2QIMAGE_H
