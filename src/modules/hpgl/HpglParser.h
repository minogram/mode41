#ifndef HPGLPARSER_H
#define HPGLPARSER_H

#include <QTextStream>
#include <QString>

class HpglParser
{
//    enum State {
//        NONE,
//        CMD,
//        WHITESPACE,
//        COMMA,
//        SEMICOLON,
//    };

private:
    HpglParser();

//    QTextStream in;
//    QString m_read;
//    void read();
//    QString peek();
public:
    static QList<QPointF> parsePoints(const QString &arg);
};

#endif // HPGLPARSER_H
