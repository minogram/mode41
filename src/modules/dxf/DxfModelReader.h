#ifndef DXFMODELREADER_H
#define DXFMODELREADER_H

#include "DxfModel.h"
#include "DxfLineReader.h"
#include "DxfReader.h"
#include <QTextStream>
#include <QStringList>

class DxfModelReader : public DxfReader
{
public:
    DxfModelReader();
    QSharedPointer<DxfModel> load(const QString &fileName);

    void reset() Q_DECL_OVERRIDE;
    void addSECTION(const QString &sectionName) Q_DECL_OVERRIDE;
    void addENDSEC() Q_DECL_OVERRIDE;
    void addBLOCK(QSharedPointer<DxfBlock> block) Q_DECL_OVERRIDE;
    void addENDBLK() Q_DECL_OVERRIDE;
    void addENTITY(QSharedPointer<DxfEntity> entity) Q_DECL_OVERRIDE;
    void addVERTEX(QSharedPointer<DxfVertex> vertex) Q_DECL_OVERRIDE;
    void addSEQEND() Q_DECL_OVERRIDE;
    void addEOF() Q_DECL_OVERRIDE;

private:
    QSharedPointer<DxfModel> m_model;
    QString curr_section = "";
    QSharedPointer<DxfBlock> curr_block;
    QSharedPointer<DxfEntity> curr_entity;
    QSharedPointer<DxfPolyline> last_polyline;
    QSharedPointer<DxfEntityList> entityList;
};

#endif // DXFMODELREADER_H
