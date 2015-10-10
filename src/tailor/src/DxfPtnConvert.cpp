#include "DxfPtnConvert.h"
#include "DxfModel.h"
#include "PtnModel.h"

#include <QStringList>
#include <QRegExp>
#include <QDebug>
#include <QSharedPointer>

using namespace dxf;

DxfPtnConvert::DxfPtnConvert()
{
}

bool splitPrefixValue(const QString &line, const QString &prefix, QString &value)
{
    if (line.startsWith(prefix, Qt::CaseInsensitive)) {
        value = line.mid(prefix.size()).trimmed();
        return true;
    }
    return false;
}

QSharedPointer<PtnDesign> DxfPtnConvert::convert(QSharedPointer<DxfModel> dxf)
{
    auto ptn = QSharedPointer<PtnDesign>::create(); // std::make_shared<PtnDesign>();

    foreach (auto block, dxf->blocks)
    {
        auto piece = QSharedPointer<PtnPiece>::create(); //new PtnPiece();
        QString blockName = block->name;
        QRegExp rx("\\_");
        QStringList query = block->name.split(rx);
        piece->name = query.at(0);
        piece->size = query.at(1);
        ptn->pieces.append(piece);

        foreach (auto entity, block->entities)
        {
            if (entity->type == dxf::EntityType::TEXT)
            {
                auto dxfText = qSharedPointerCast<DxfText>(entity);
                QString text = dxfText->text;
                QString layer = dxfText->layer;
                if (layer == "1")
                {
                    QString value;
                    if (splitPrefixValue(text, "ANNOTATION:", value)) {
                        //qDebug() << text;
                    } else if (splitPrefixValue(text, "QUANTITY:", value)) {
                        piece->quantity = value.toInt();
                    } else if (splitPrefixValue(text, "SIZE:", value)) {
                        piece->size = value;
                    } else if (splitPrefixValue(text, "MATERIAL:", value)) {
                        piece->material = value;
                    } else if (splitPrefixValue(text, "PIECE NAME:", value)) {
                        piece->name = value;
                    }
                }
            }
            else if (entity->type == dxf::EntityType::LINE)
            {
                auto dxfLine = qSharedPointerCast<DxfLine>(entity);
                auto ptnLine = QSharedPointer<PtnLine>::create();

                ptnLine->x1 = dxfLine->x1;
                ptnLine->y1 = dxfLine->y1;
                ptnLine->x2 = dxfLine->x2;
                ptnLine->y2 = dxfLine->y2;
                piece->entities.append(ptnLine);
            }
            else if (entity->type == dxf::EntityType::POLYLINE)
            {
                auto dxfPolyline = qSharedPointerCast<DxfPolyline>(entity);
                auto ptnPolyline = QSharedPointer<PtnPolyline>::create();

                foreach (auto dxfVertex, dxfPolyline->vertices)
                {
                    auto ptnVertex = QSharedPointer<PtnVertex>::create();
                    ptnVertex->x = dxfVertex->x;
                    ptnVertex->y = dxfVertex->y;

                    ptnPolyline->vertices.append(ptnVertex);
                }
                ptnPolyline->setClosed(dxfPolyline->isClosed());
                piece->entities.append(ptnPolyline);
            }
        }
    }

    return ptn;
}


