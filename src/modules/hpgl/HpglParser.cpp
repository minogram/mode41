#include "HpglParser.h"
#include <QtCore>

QList<QPointF> HpglParser::parsePoints(const QString &arg)
{
    QList<QPointF> points;

    auto args = arg.split(",");
    //Q_ASSERT(args.size() % 2 == 0);

    for (int i=0; i<args.size(); i+=2)
    {
        float x = args[i].toFloat();
        if (i+1 < args.size())
        {
            float y = args[i+1].toFloat();
            points.append(QPointF(x, y));
        }
    }
    return points;
}

