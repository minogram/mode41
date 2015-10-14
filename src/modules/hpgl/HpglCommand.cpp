#include "Hpgl.h"

HpglCommand::HpglCommand(const QString &name, const QString &arg)
{
    if (name == "PA" || name == "PR" || name == "PD" || name == "PU")
    {
        auto points = HpglParser::parsePoints(arg);
        m_name = name;
        m_argument.setValue(points);
    }
    else
    {
        m_name = name;
        m_argument = arg;
    }
}

