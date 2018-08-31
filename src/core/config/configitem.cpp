#include "configitem.hpp"

#include <ShellScalingApi.h>

ConfigItem::ConfigItem()
    : m_object()
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
    const static float factor = static_cast<float>(GetScaleFactorForDevice(DEVICE_PRIMARY)) / 100.0f;
    return factor * value;
}

int ConfigItem::scale(int value)
{
    return scale(static_cast<float>(value));
}
