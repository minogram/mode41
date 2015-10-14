#include <QtCore>
#include <QException>
#include <QDebug>
#include <QtCore>
#include "HpglTextReader.h"
#include "HpglDocument.h"

HpglTextReader::HpglTextReader()
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

QSharedPointer<HpglDocument> HpglTextReader::load(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        throw QException();
    }

    in.setDevice(&file);

    m_doc = QSharedPointer<HpglDocument>::create();

    //m_doc = QSharedPointer<HpglDocument>::create();

    qDebug()<< "===============================";

    while (!in.atEnd())
    {
        auto line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        auto i = m_regex.globalMatch(line);
        while (i.hasNext()) {
            auto match = i.next();
            doCmd(match.captured());
        }
    }

    file.close();
    return m_doc;
}

void HpglTextReader::doCmd(const QString &line)
{
    if (line.isEmpty()) return;

    //Q_ASSERT(!line.contains(";"));
    //qDebug() << cmd;
    auto name = line.mid(0, 2);
    auto argument = line.mid(2);
    HpglCommand cmd(name, argument);

    m_doc->items.append(cmd);
}
