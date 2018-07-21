#include "configabstract.hpp"

ConfigAbstract::ConfigAbstract()
{

}

ConfigAbstract::ConfigAbstract(const QJsonObject &object)
    : m_object(object)
{

}

ConfigAbstract::~ConfigAbstract()
{

}

QJsonObject ConfigAbstract::object() const
{
    return m_object;
}

void ConfigAbstract::set(const QString &key, const QJsonValue &value)
{
    m_object.insert(key, value);
}

QJsonValue ConfigAbstract::get(const QString &key)
{
    return m_object.value(key);
}

void ConfigAbstract::setDefault(const QString &key, const QJsonValue &value)
{
    if (!m_object.contains(key))
         m_object.insert(key, value);
}

float ConfigAbstract::scale(float value)
{
    return (GetScaleFactorForDevice(DEVICE_PRIMARY) / 100.0) * value;
}

int ConfigAbstract::scale(int value)
{
    return static_cast<int>(scale(static_cast<float>(value)));
}

int ConfigAbstract::makeEven(int value)
{
    return value % 2 == 0 ? value : --value;
}
