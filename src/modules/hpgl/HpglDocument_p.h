#ifndef HPGLDOCUMENT_P_H
#define HPGLDOCUMENT_P_H

#include <QtCore>
#include "HpglCommand.h"

class HpglDocumentPrivate : public QSharedData
{
public:
    QList<HpglCommand> items;
};

#endif // HPGLDOCUMENT_P_H

