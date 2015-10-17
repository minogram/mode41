#include <QtCore>
#include "HpglReader.h"
#include "HpglCommand.h"
#include "HpglDocument.h"
#include "HpglReference.h"

bool HpglReader::g_initialized = false;
QRegularExpression HpglReader::g_regex;
HpglReference g_refer;

HpglReader::HpglReader()
{
    initialize();
    reference().build0();
}

void HpglReader::initialize()
{
    if (g_initialized) return;

    g_initialized = true;

    QStringList patterns;
// patterns.append("\\x1B%-1B");
// patterns.append("\\x1B");                   // [ESC]%-1B
// patterns.append("(?s-imnx:LB.*?\\x03)");    //LB ... [ETX]
// patterns.append(           "(?sm-inx:LB.*?^;)" "|"     // LB ... ^;
    patterns.append("[A-Z]{2}[0-9,*\\-\\.]*"); // 2 letters and numbers

    Q_ASSERT(patterns.size() > 0);

    QString pattern;

    if (patterns.size() == 1) {
        pattern = patterns.at(0);
    } else {
        pattern += "(";
        pattern += patterns.join(")|(");
        pattern += ")";
    }

    g_regex.setPattern(pattern);
    g_regex.setPatternOptions(QRegularExpression::MultilineOption);

    //=================
}

HpglDocument HpglReader::load(const QString &filePath)
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

        auto i = g_regex.globalMatch(line);
        while (i.hasNext()) {
            auto match = i.next();
            auto src = match.captured();
            auto cmd = parseCommand(src);
            if (!cmd.isNull())
                doc.items().push_back(cmd);
        }
    }

    file.close();
    return doc;
}

HpglCommand HpglReader::parseCommand(const QString &src)
{
    auto name = src.mid(0, 2);
    auto arg = src.mid(2);

    if (m_reference.canIgnore(name))
    {
        return HpglCommand(nullptr);
    }

    if (reference().hasInfo(name))
    {
        auto param = reference().param(name);
        if (param.isEmpty())
            return HpglCommand(name);

        auto &args = parseArgs(arg, param);
        return HpglCommand(name, args);

//        if (param == "p*") {
//            return HpglCommand(name, parseArgs(argu, "p*"));
////            auto points = parsePoints(argu);
////            return HpglCommand(name, points);
//        }
//        else if (param == "n") {
//            auto i = argu.toInt();
//            return HpglCommand(name, i);
//        }
//        else if (param == "n*") {
//            return HpglCommand(name);
//        }
//        else if (param == "f*") {
//            auto args = parseFloats(argu);
//            return HpglCommand(name, args);
//        }
//        else if (param == "") {
//            return HpglCommand(name);
//        }
//        else {
//            return HpglCommand(name, param);
//        }
    }
    else
    {
        // unknown command
        qDebug() << "UNKNOWN HPGL: " << src;
        return HpglCommand(nullptr);
    }
}

QList<int> HpglReader::parseInts(const QString &arg)
{
    QList<int> args;
    if (arg.isNull() || arg.isEmpty()) return args;

    auto tokens = arg.split(',');
    for (int i=0; i<tokens.size(); i++)
        args.append(tokens[i].toInt());
    return args;
}

QList<float> HpglReader::parseFloats(const QString &arg)
{
    QList<float> args;
    if (arg.isNull() || arg.isEmpty()) return args;

    auto tokens = arg.split(',');
    for (int i=0; i<tokens.size(); i++)
        args.append(tokens[i].toFloat());
    return args;
}

QList<QPointF> HpglReader::parsePoints(const QString &arg)
{
    QList<QPointF> points;

    if (arg.isNull() || arg.isEmpty()) return points;

    auto tokens = arg.split(',');

    Q_ASSERT(tokens.size() % 2 == 0);

    for (int i=0; i<tokens.size(); i+=2)
    {
        float x = tokens[i].toFloat();
        float y = tokens[i+1].toFloat();
        points.append(QPointF(x, y));
    }
    return points;
}

QVariantList HpglReader::parseArgs(const QString &arg, const QString& format)
{
    QVariantList result;
    if (arg.isNull() || arg.isEmpty())
        return result;

    if (format == "n") {
        result << arg.toInt();
    } else if (format == "n*") {
        auto tokens = arg.split(',');
        foreach (auto token, tokens)
            result << token.toInt();
    } else if (format == "f*") {
        auto tokens = arg.split(',');
        foreach (auto token, tokens)
            result << token.toFloat();
    } else if (format == "p*") {
        auto tokens = arg.split(',');
        Q_ASSERT(tokens.size() % 2 == 0);
        for (int i=0; i<tokens.size(); i+=2) {
            float x = tokens[i].toFloat();
            float y = tokens[i+1].toFloat();
            result << QPointF(x, y);
        }
    }
    return result;
}
