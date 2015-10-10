#ifndef DXFAAMAREADER_H
#define DXFAAMAREADER_H

#include "DxfModel.h"
#include "DxfReader.h"
#include <QDebug>
#include <QString>
#include <QTextStream>

class QObject;

class DxfAamaReader : public QObject
{
    Q_OBJECT

public:
    DxfAamaReader(QObject *parent = 0);
    dxf::DxfModel *load(QString fileName);
    //QString &section() { return m_section; }
private:
    dxf::DxfReader r;
    //QString m_section;
    dxf::DxfModel *m_model;
    //dxf::DxfPolyline *m_polyline;

private:
    void readAll();

    void readSECTIONS();
    void readSECTION();
//    void readHEADER();
    void readBLOCKS(dxf::DxfBlockList &list);
    void readBLOCK(dxf::DxfBlockList &list);

    void readENTITIES();
    void readENTITY(dxf::DxfEntityList &list);
    void readTEXT(dxf::DxfEntityList &list);
    void readPOINT(dxf::DxfEntityList &list);
    void readLINE(dxf::DxfEntityList &list);
    void readPOLYLINE(dxf::DxfEntityList &list);
    void readVERTEX(dxf::DxfVertexList &list);
    void readENDSEQ();
};
#endif // DXFAAMAREADER_H
