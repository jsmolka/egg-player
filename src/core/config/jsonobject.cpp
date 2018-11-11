#include "jsonobject.hpp"

#include <ShellScalingApi.h>

float cfg::JsonObject::scale(float value)
{
    static const float factor = static_cast<float>(GetScaleFactorForDevice(DEVICE_PRIMARY)) / 100.0f;

    return factor * value;
}

int cfg::JsonObject::scale(int value)
{
    return qRound(scale(static_cast<float>(value)));
}

void cfg::JsonObject::set(const QString &key, const QJsonValue &value)
{
    m_object.insert(key, value);
}

QJsonValue cfg::JsonObject::get(const QString &key) const
{
    return m_object.value(key);
}

void cfg::JsonObject::setDefault(const QString &key, const QJsonValue &value)
{
    if (!m_object.contains(key))
         set(key, value);
}
