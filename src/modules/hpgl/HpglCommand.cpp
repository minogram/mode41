#include "HpglCommand.h"
#include "HpglTextReader.h"
#include <QtCore>

HpglCommand::HpglCommand(const QString &name, const QString &arg)
{
    if (name == "PA" || name == "PR" || name == "PD" || name == "PU")
    {
        auto points = HpglTextReader::parsePoints(arg);
        m_name = name;
        m_argument.setValue(points); // = points;
        //m_argument.setValue(points);
    }
    else
    {
        m_name = name;
        m_argument = arg;
    }
}

