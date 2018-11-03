#include "cfgbase.hpp"

#ifdef Q_OS_WIN
#include <ShellScalingApi.h>
#endif

float cfg::Base::scale(float value)
{
#ifdef Q_OS_WIN
    static const float factor = static_cast<float>(GetScaleFactorForDevice(DEVICE_PRIMARY)) / 100.0f;
#else
    static const float factor = 1.0f;
#endif

    return factor * value;
}

int cfg::Base::scale(int value)
{
    return qRound(scale(static_cast<float>(value)));
}

void cfg::Base::set(const QString &key, const QJsonValue &value)
{
    m_object.insert(key, value);
}

QJsonValue cfg::Base::get(const QString &key) const
{
    return m_object.value(key);
}

void cfg::Base::setDefault(const QString &key, const QJsonValue &value)
{
    if (!m_object.contains(key))
         m_object.insert(key, value);
}
