#ifndef DXFLINEREADER_H
#define DXFLINEREADER_H

#include <QTextStream>

class DxfLineReader
{
public:
    DxfLineReader();
    void setDevice(QIODevice *device);

protected:
    ///
    /// \brief atEnd
    /// \return true, if end of file.
    ///
    bool atEnd();

    ///
    /// \brief readZero
    /// \return
    /// read group code 0
    ///
    bool readZero();

    ///
    /// \brief readNoZero
    /// \return
    /// read group code non 0
    ///
    bool readNoZero();

    /// \brief DxfLineReader::skip
    /// skip lines until next code 0 in dxf file.
    /// after skip(), the current is code 0 or EOF.
    void skip();

    int code() const { return m_code; }
    const QString &value() { return m_value; }

private:
    ///
    /// \brief moveNext
    /// \return true
    /// move positon to next pair
    ///
    bool moveNext();

    ///
    /// \brief peekNext
    /// \return
    ///
    bool peekNext();

private:
    QTextStream in;
    int m_lineNumber = 0;

    int m_code = 0;
    QString m_value = "";

    bool m_peekNext = false;
    int m_codeNext = 0;
    QString m_valueNext;
};

#endif // DXFLINEREADER_H
