#include "FreeImage2QImage.h"

#include <QFileInfo>
#include <QColor>
#include <QImage>
#include <FreeImage.h>

FreeImage2QImage::FreeImage2QImage()
{
}

QImage FreeImage2QImage::load(const QString &filePath)
{
    // todo: check freeimage_initailise() no need?
//    FreeImage_Initialise();

//    auto version = FreeImage_GetVersion();
//    qDebug() << version;
//    qDebug() << FreeImage_GetCopyrightMessage();

    QFileInfo fileInfo(filePath);
    auto ba_str = fileInfo.absoluteFilePath().toLatin1();

    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(ba_str);

    auto  fi = FreeImage_Load(format, ba_str.data());
    auto image = FIBitmapToQImage(fi);
    FreeImage_Unload(fi);
    return image;

    //    FreeImage_DeInitialise();
}

QImage& FreeImage2QImage::QImageNone()
{
    static QImage none(0, 0, QImage::Format_Invalid);
    return none;
}

bool FreeImage2QImage::IsQImageNone(const QImage& img)
{
    return img == QImageNone();
}

QVector<QRgb>& FreeImage2QImage::PaletteNone()
{
    static QVector<QRgb> none = QVector<QRgb>();
    return none;
}

bool FreeImage2QImage::IsPaletteNone(const QVector<QRgb>& pal)
{
    return pal == PaletteNone();
}

QVector<QRgb> FreeImage2QImage::GetPalette(FIBITMAP *dib)
{
    if (dib != NULL &&  FreeImage_GetBPP(dib) <= 8)
    {
        RGBQUAD *pal = FreeImage_GetPalette(dib);
        int nColors   = FreeImage_GetColorsUsed(dib);
        QVector<QRgb> result(nColors);
        for (int i = 0; i < nColors; ++i) // first pass
        {
            QColor c(pal[i].rgbRed,pal[i].rgbBlue,pal[i].rgbBlue, 0xFF);
            result[i] = c.rgba();
        }
        if (FreeImage_IsTransparent(dib)) // second pass
        {
            BYTE *transpTable = FreeImage_GetTransparencyTable(dib);
            int nTransp = FreeImage_GetTransparencyCount(dib);
            for (int i = 0; i  < nTransp; ++i)
            {
                QRgb c = result[i];
                result[i] = qRgba(qRed(c),qGreen(c),qBlue(c),transpTable[i]);
            }
        }
        return result;
    }
    return PaletteNone();
}

QImage FreeImage2QImage::FIBitmapToQImage(FIBITMAP *dib)
{
    //FreeImage_GetFileType()
    //FreeImage_GetFileTypeU();

    if (!dib || FreeImage_GetImageType(dib) != FIT_BITMAP)
        return QImageNone();
    int width  = FreeImage_GetWidth(dib);
    int height = FreeImage_GetHeight(dib);

    switch (FreeImage_GetBPP(dib))
    {
    case 1:
        {
            QImage result(width,height,QImage::Format_Mono);
            FreeImage_ConvertToRawBits(
                result.scanLine(0), dib, result.bytesPerLine(), 1, 0, 0, 0, true);
            return result;
        }
    case 4: // NOTE: QImage do not support 4-bit, convert it to 8-bit
        {
            QImage result(width,height,QImage::Format_Indexed8);
            FreeImage_ConvertToRawBits(
                result.scanLine(0), dib, result.bytesPerLine(), 8, 0, 0, 0, true);
            return result;
        }
    case 8:
        {
            QImage result(width,height,QImage::Format_Indexed8);
            FreeImage_ConvertToRawBits(
                result.scanLine(0), dib, result.bytesPerLine(), 8, 0, 0, 0, true);
            return result;
        }
    case 16:
        if ((FreeImage_GetRedMask(dib)   == FI16_555_RED_MASK) &&
            (FreeImage_GetGreenMask(dib) == FI16_555_GREEN_MASK) &&
            (FreeImage_GetBlueMask(dib)  == FI16_555_BLUE_MASK))
        {
            QImage result(width,height,QImage::Format_RGB555);
            FreeImage_ConvertToRawBits(
                result.scanLine(0), dib, result.bytesPerLine(), 16,
                FI16_555_RED_MASK, FI16_555_GREEN_MASK, FI16_555_BLUE_MASK,
                true);
            return result;
        }
        else /* 565 */
        {
            QImage result(width,height,QImage::Format_RGB16);
            FreeImage_ConvertToRawBits(
                result.scanLine(0), dib, result.bytesPerLine(), 16,
                FI16_565_RED_MASK, FI16_565_GREEN_MASK, FI16_565_BLUE_MASK,
                true);
            return result;
        }
    case 24:
        {
            QImage result(width,height,QImage::Format_RGB32);
            FreeImage_ConvertToRawBits(
                result.scanLine(0), dib, result.bytesPerLine(), 32,
                FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK,
                true);
            return result;
        }
    case 32:
        {
            QImage result(width,height,QImage::Format_ARGB32);
            FreeImage_ConvertToRawBits(
                result.scanLine(0), dib, result.bytesPerLine(), 32,
                FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK,
                true);
            return result;
        }
    default:
        break;
    }
    return QImageNone();
}
