#include "SketchModel.h"
#include <QtCore>
#include <QtXml>
#include <QDomDocument>

SketchModel::SketchModel()
{
}

void SketchModel::load(const QString &filePath)
{
    QDomDocument doc("sketch2010");
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly))
        return;

    if (!doc.setContent(&file)) {
        file.close();
        return;
    }

    m_dom = doc;
    readDrawing();

    qDebug() << "ok";

    file.close();
}

void SketchModel::readDrawing()
{
    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = m_dom.documentElement();

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            qDebug() << qPrintable(e.tagName()) << endl; // the node really is an element.
        }
        n = n.nextSibling();
    }
}
