#include <QImageIOHandler>
#include <QDebug>
#include "PsdHandler.h"
#include "FreeImage.h"
#include "QFreeImage.h"

///
/// \brief The PdsPlugin class
/// https://github.com/informationsea/Qt-JPEGXR
class PdsPlugin : public QImageIOPlugin
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QImageIOHandlerFactoryInterface" FILE "psd.json")
#endif

public:
    //PdsPlugin(QObject *parent = 0);

    QStringList keys() const;
    Capabilities capabilities(QIODevice *device,const QByteArray &format) const;
    QImageIOHandler *create(QIODevice *device, const QByteArray &format = QByteArray()) const;
};

//PdsPlugin::PdsPlugin(QObject *parent)
//    : QImageIOPlugin(parent)
//{
//     qDebug() << Q_FUNC_INFO;
//}

QStringList PdsPlugin::keys() const
{
     return QStringList() << QLatin1String("xxx");
}

QImageIOPlugin::Capabilities PdsPlugin::capabilities(QIODevice *device, const QByteArray &format) const
{
//    if (!format .isEmpty())
//        return 0;
//    if (!device->isOpen())
//        return 0;

    Capabilities cap;
    FREE_IMAGE_FORMAT fif = QFreeImage::GetFIF(device, format);
    if (device->isReadable() && FreeImage_FIFSupportsReading(fif))
        cap |= CanRead;
    return cap;
}

QImageIOHandler *PdsPlugin::create(QIODevice *device, const QByteArray &format) const
{
    auto psdHandler = new PsdHandler();
    psdHandler->setDevice(device);
    psdHandler->setFormat(format);
    return psdHandler;
}

//#if QT_VERSION < 0x050000
//Q_EXPORT_PLUGIN2(Psd, PsdPlugin)
//#endif /

