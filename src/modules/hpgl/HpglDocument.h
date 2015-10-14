#ifndef HPGLDOCUMENT_H
#define HPGLDOCUMENT_H

#include "HpglCommand.h"
#include <QtCore>

class HpglDocument
{
public:
    HpglDocument();

    QList<HpglCommand> items;
};


#endif // HPGLDOCUMENT_H
