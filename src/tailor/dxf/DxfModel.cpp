#include "DxfModel.h"

namespace dxf
{

DxfObject::DxfObject()
{
}

DxfModel::DxfModel()
    : DxfObject()
{
}

DxfBlock::DxfBlock()
    : DxfObject()
{
}

DxfEntity::DxfEntity(EntityType _type)
    : DxfObject()
    , type(_type)
{
}

DxfInsert::DxfInsert()
    :DxfEntity(EntityType::INSERT)
{
}

DxfVertex::DxfVertex()
    : DxfEntity(EntityType::POINT)
{
}

DxfText::DxfText()
    : DxfEntity(EntityType::TEXT)
{
}

DxfPoint::DxfPoint()
    : DxfEntity(EntityType::POINT)
{
}

DxfLine::DxfLine()
    : DxfEntity(EntityType::LINE)
{
}

DxfPolyline::DxfPolyline()
    : DxfEntity(EntityType::POLYLINE)
    , flags(0)
{
}

}
