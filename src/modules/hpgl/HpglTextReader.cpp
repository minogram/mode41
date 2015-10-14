#include <QtCore>
#include <QException>
#include <QDebug>
#include <QtCore>
#include "HpglTextReader.h"
#include "HpglDocument.h"

HpglTextReader::HpglTextReader()
{
////    var patterns = new string[]
////               {
////                   //@"\x1B\x25\x2D1B",      // [ESC]%-1B
////                   @"\x1B%-1B",            // [ESC]%-1B
////                   @"\x1B",                // [ESC]

////                   @"(?s-imnx:LB.*?\x03)", // LB ... [ETX]
////                   @"(?sm-inx:LB.*?^;)",   // LB ... ^;

////                   @"[A-Z]{2}[0-9,*\-\.]*", // AA....
////               };

////               return string.Format(@"({0})", string.Join("|", patterns));

    QString pattern =
            "[A-Z]{2}[0-9,*\\-\\.]*"; // 2 letters and numbers

    m_regex.setPattern(pattern);
    m_regex.setPatternOptions(QRegularExpression::MultilineOption);
}

HpglDocument HpglTextReader::load(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        throw QException();
    }
    QTextStream in(&file);

    HpglDocument doc;

    while (!in.atEnd())
    {
        auto line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        auto i = m_regex.globalMatch(line);
        while (i.hasNext()) {
            auto match = i.next();
            auto cmd = match.captured();
            auto name = cmd.mid(0, 2);
            auto argument = cmd.mid(2);
            doc.items().append(HpglCommand(name, argument));
        }
    }

    file.close();
    return doc;
}

QList<QPointF> HpglTextReader::parsePoints(const QString &arg)
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
