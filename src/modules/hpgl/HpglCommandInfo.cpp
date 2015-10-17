#include "HpglCommandInfo.h"

HpglCommandInfo::HpglCommandInfo()
{
}

HpglCommandInfo::HpglCommandInfo(const HpglCommandInfo &other)
{
    m_name = other.m_name;
    m_param = other.m_param;
    m_description = other.m_description;
}

HpglCommandInfo::HpglCommandInfo(const QString &name, const QString &param, const QString &description)
{
    m_name = name;
    m_param = param;
    m_description = description;
};
