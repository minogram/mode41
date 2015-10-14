#ifndef FREEIMAGE2QIMAGE_H
#define FREEIMAGE2QIMAGE_H

#include <QImage>
#include <FreeImage.h>

///
/// \brief The FreeImage2QImage class
///
/// original source is
/// https://github.com/zoon/FreeImage-Plugin-for-QT4
///
class QFreeImage
{
private:
    QFreeImage();

public:
    static QImage load(const QString &filePath);

private:
    static QImage& QImageNone();
    static bool IsQImageNone(const QImage& qi);
    static QVector<QRgb>& PaletteNone();
    static bool IsPaletteNone(const QVector<QRgb> &pal);
    static QVector<QRgb> GetPalette(FIBITMAP *dib);
    static QImage FIBitmapToQImage(FIBITMAP *dib);
};

#endif // FREEIMAGE2QIMAGE_H
