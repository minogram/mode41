#include "PtnModel.h"

PtnObject::PtnObject()
{
}

PtnVertex::PtnVertex()
    : PtnObject()
{
}

PtnDesign::PtnDesign()
    : PtnObject()
{
}

PtnEntity::PtnEntity(PtnEntityType _type)
    : PtnObject()
{
    type = _type;
}

PtnText::PtnText()
    : PtnEntity(PtnEntityType::Text)
{
}

PtnLine::PtnLine()
    : PtnEntity(PtnEntityType::Line)
{
}

PtnPolyline::PtnPolyline()
    : PtnEntity(PtnEntityType::Polyline)
{
}

bool PtnPolyline::isClosed()
{
    return closed;
}

void PtnPolyline::setClosed(bool closed)
{
    PtnPolyline::closed = closed;
}

PtnPiece::PtnPiece()
    : PtnObject()
{
}

