#ifndef DXFREADER_H
#define DXFREADER_H

#include "DxfModel.h"
#include "DxfLineReader.h"
#include <QTextStream>
#include <QStringList>

using namespace dxf;

class DxfReader : public DxfLineReader
{
public:
    DxfReader();

protected:
    void loadCore(const QString &fileName);

private:
    void readAll();
    void readSECTION();
    void readENDSEC();
    void readBLOCK();
    void readENDBLK();
    void readINSERT();
    void readTEXT();
    void readLINE();
    void readPOINT();
    void readPOLYLINE();
    void readVERTEX();
    void readSEQEND();

protected:
    virtual void reset() = 0;
    virtual void addSECTION(const QString &sectionName) = 0;
    virtual void addENDSEC() = 0;
    virtual void addBLOCK(QSharedPointer<DxfBlock> block) = 0;
    virtual void addENDBLK() = 0;
    virtual void addENTITY(QSharedPointer<DxfEntity> entity) = 0;
    virtual void addVERTEX(QSharedPointer<DxfVertex> vertex) = 0;
    virtual void addSEQEND() = 0;
    virtual void addEOF() = 0;
};

#endif // DXFREADER_H
