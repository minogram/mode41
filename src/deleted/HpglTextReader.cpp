#include "HpglTextReader.h"
#include <QFile>
#include <QTextStream>
#include <QException>
#include <QDebug>

HpglTextReader::HpglTextReader()
{

}

void HpglTextReader::load(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        throw QException();
    }

    in.setDevice(&file);

    //m_doc = QSharedPointer<HpglDocument>::create();

    while (!in.atEnd())
    {
        auto line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        qDebug() << line;

        int start =0;
        int pos = 0;
        //for (int len = start; end < line.size();)
        while (true)
        {
            if (pos == line.size()) break;

            QChar ch = line.at(pos);

            if (ch == ';') {
                auto line1 = line.mid(start, pos-start+1).trimmed();
                addLine(line1);
                pos++;
                start = pos;
            }
            else
            {
                pos++;
            }
        }
        //addLine(line.trimmed());
    }

    file.close();

    //return m_doc;
}

void HpglTextReader::addLine(const QString &line)
{
    //Q_ASSERT(!line.contains(";"));
    //Q_ASSERT(line.at(0).isLetter());
    //Q_ASSERT(line.at(1).isLetter());

    //qDebug() << line;
}
