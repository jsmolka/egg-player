#include "cfgabstract.hpp"

CfgAbstract::CfgAbstract()
{

}

CfgAbstract::CfgAbstract(QJsonObject object)
    : m_object(object)
{

}

QJsonObject CfgAbstract::object() const
{
    return m_object;
}

void CfgAbstract::setDefault(const QString &key, const QJsonValue &value)
{
    if (!m_object.contains(key))
        m_object.insert(key, value);
}

float CfgAbstract::scale(float value)
{
    return (GetScaleFactorForDevice(DEVICE_PRIMARY) / 100.0) * value;
}

int CfgAbstract::scale(int value)
{
    return static_cast<int>(scale(static_cast<float>(value)));
}

int CfgAbstract::makeEven(int value)
{
    return value % 2 == 0 ? value : --value;
}
