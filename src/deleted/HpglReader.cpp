#include "HpglReader.h"
#include "HpglDocument.h"
#include <QSharedPointer>
#include <QFile>
#include <QIODevice>
#include <QException>
#include <QDebug>

HpglReader::HpglReader()
{

}

//public abstract class TextParser
// {
//     protected StreamReader _reader;
//     private char? readed;
//     protected char peek()
//     {
//         if (readed == null)
//         {
//             read();
//         }
//         return readed.Value;
//     }

//     protected void read()
//     {
//         readed = (char)_reader.Read();
//     }
// }

//QString HpglReader::peek()
//{
//    if (m_read.isEmpty())
//    {
//        read();
//    }
//    return m_read;
//}

//void HpglReader::read()
//{
//    m_read = in.read(1);
//}

QSharedPointer<HpglDocument> HpglReader::load(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        throw QException();
    }

    in.setDevice(&file);

    m_doc = QSharedPointer<HpglDocument>::create();

    while (!in.atEnd())
    {
        auto line = in.readLine();
        parse(line);
    }

    file.close();

    return m_doc;
}

void HpglReader::parse(const QString &data)
{
    auto lines = data.split(";");
    foreach (auto line, lines) {
        auto trimmed = line.trimmed();
        if (trimmed.isEmpty()) return;
        if (trimmed.size() < 2) return; // error

        auto cmd = trimmed.mid(0, 2);
        auto arg = trimmed.mid(2).trimmed();

      /*  if (cmd == "PD") {
            QList<QPointF> points;
            parsePoints(arg, points);
            auto item = QSharedPointer<HpglPD>::create(points);
            m_doc->items.append(item);
        }
        else if (cmd == "PU") {
            QList<QPointF> points;
            parsePoints(arg, points);
            auto item = QSharedPointer<HpglPU>::create(points);
            m_doc->items.append(item);
        }
        else if (cmd == "PA") {
            QList<QPointF> points;
            parsePoints(arg, points);
            auto item = QSharedPointer<HpglPA>::create(points);
            m_doc->items.append(item);
        }
        else if (cmd == "PR") {
            QList<QPointF> points;
            parsePoints(arg, points);
            auto item = QSharedPointer<HpglPR>::create(points);
            m_doc->items.append(item);
        }
        else*/ {
            qDebug() << line;
        }
    }
}

void HpglReader::parsePoints(const QString &arg, QList<QPointF> &points)
{
    auto args = arg.split(",");
    for (int i=0; (i+1)<args.size();) {
        double x = args[i].toDouble();
        i++;
        double y = args[i].toDouble();
        i++;
        QPointF p(x, y);
        points.append(p);
    }
}




