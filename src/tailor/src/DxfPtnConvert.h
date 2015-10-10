#ifndef DXFPTNCONVERT_H
#define DXFPTNCONVERT_H

/*
 *  dxf_line
 *
 *
 *
 */

#include "DxfModel.h"
#include "PtnModel.h"
#include <QSharedPointer>

using namespace dxf;

class DxfPtnConvert
{
public:
    DxfPtnConvert();
    QSharedPointer<PtnDesign> convert(QSharedPointer<DxfModel> dxf);
};

#endif // DXFPTNCONVERT_H
