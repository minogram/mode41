#include "HpglParser.h"
#include <QtCore>

HpglParser::HpglParser()
{
    //    var patterns = new string[]
    //               {
    //                   //@"\x1B\x25\x2D1B",      // [ESC]%-1B
    //                   @"\x1B%-1B",            // [ESC]%-1B
    //                   @"\x1B",                // [ESC]

    //                   @"(?s-imnx:LB.*?\x03)", // LB ... [ETX]
    //                   @"(?sm-inx:LB.*?^;)",   // LB ... ^;

    //                   @"[A-Z]{2}[0-9,*\-\.]*", // AA....
    //               };

    //               return string.Format(@"({0})", string.Join("|", patterns));

        QString pattern =
                "[A-Z]{2}[0-9,*\\-\\.]*"; // 2 letters and numbers

        m_regex.setPattern(pattern);
        m_regex.setPatternOptions(QRegularExpression::MultilineOption);
}

void HpglParser::parseCommand(const QString &data)
{

}

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

