#ifndef PSDHANDLER_H
#define PSDHANDLER_H

#include <QImageIOHandler>
#include <QImage>
#include <QDebug>
#include "FreeImage.h"

class PsdHandler : public QImageIOHandler
{
public:
    PsdHandler();

    bool canRead() const Q_DECL_OVERRIDE;
    bool read(QImage *image) Q_DECL_OVERRIDE;
    //bool write(const QImage &image) Q_DECL_OVERRIDE;

    QByteArray name() const Q_DECL_OVERRIDE;

    QVariant option(ImageOption option) const Q_DECL_OVERRIDE;
    void setOption(ImageOption option, const QVariant &value) Q_DECL_OVERRIDE;
    bool supportsOption(ImageOption option) const Q_DECL_OVERRIDE;

};

#endif // PSDHANDLER_H
