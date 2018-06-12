#include "configitem.hpp"

ConfigItem::ConfigItem()
{

}

ConfigItem::ConfigItem(const QJsonObject &object)
    : m_object(object)
{

}

ConfigItem::~ConfigItem()
{

}

QJsonObject ConfigItem::object() const
{
    return m_object;
}

void ConfigItem::set(const QString &key, const QJsonValue &value)
{
    m_object.insert(key, value);
}

QJsonValue ConfigItem::get(const QString &key)
{
    return m_object.value(key);
}

void ConfigItem::setDefault(const QString &key, const QJsonValue &value)
{
    if (!m_object.contains(key))
         m_object.insert(key, value);
}

float ConfigItem::scale(float value)
{
    return (GetScaleFactorForDevice(DEVICE_PRIMARY) / 100.0) * value;
}

int ConfigItem::scale(int value)
{
    return static_cast<int>(scale(static_cast<float>(value)));
}

int ConfigItem::makeEven(int value)
{
    return value % 2 == 0 ? value : --value;
}
