#include "DxfModelReader.h"
#include "DxfReader.h"
#include "DxfLineReader.h"
#include "DxfModel.h"
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QException>
#include <QSharedPointer>

using namespace dxf;

DxfModelReader::DxfModelReader()
    : DxfReader()
{
}

QSharedPointer<DxfModel> DxfModelReader::load(const QString &fileName)
{
    loadCore(fileName);
    return m_model;
}

void DxfModelReader::reset()
{
    m_model = QSharedPointer<DxfModel>::create();
    curr_section = "";
    curr_block.clear();
    curr_entity.clear();
    last_polyline.clear();
    entityList.clear();
}

void DxfModelReader::addSECTION(const QString &sectionName)
{
    curr_section = sectionName;
}

void DxfModelReader::addENDSEC()
{
    curr_section.clear();
}

void DxfModelReader::addBLOCK(QSharedPointer<DxfBlock> block)
{
    //Q_ASSERT(m_model);
    //Q_ASSERT(block);

    //m_model->blocks.append(block);
    curr_block = block;
    m_model->blocks.append(block);
}

void DxfModelReader::addENDBLK()
{
    curr_block.clear();
}

void DxfModelReader::addENTITY(QSharedPointer<DxfEntity> entity)
{
    Q_ASSERT(entity);

    if (entity->type == EntityType::POLYLINE)
    {
        last_polyline = entity.staticCast<DxfPolyline>();
    }
    else
    {
        last_polyline.clear();
    }

    if (curr_section == "BLOCKS") {
        Q_ASSERT(curr_block);
        curr_block->entities.append(entity);
    } else if (curr_section == "ENTITIES") {
        m_model->entities.append(entity);
    } else {
        qDebug() << "ERROR:" << Q_FUNC_INFO;
    }
}

void DxfModelReader::addVERTEX(QSharedPointer<DxfVertex> vertex)
{
    Q_ASSERT(last_polyline);
    Q_ASSERT(vertex);

    last_polyline->vertices.append(vertex);
}

void DxfModelReader::addSEQEND()
{
    last_polyline.clear();
}

void DxfModelReader::addEOF()
{
}

