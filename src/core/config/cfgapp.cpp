#include "cfgapp.hpp"

#include "core/macros.hpp"

void cfg::App::loadObject(const QJsonObject &object)
{
    setObject(object);

    m_minimalSize.loadObject(object.value("minimalSize").toObject());
}

QJsonObject cfg::App::toObject() const
{
    QJsonObject object(this->object());
    object.insert("minimalSize", m_minimalSize.toObject());

    return object;
}

void cfg::App::setDefaults()
{
    setDefault("fontSize", 10.25);
    setDefault("log", true);

    m_minimalSize.setDefaults();
}

const cfg::app::MinimalSize &cfg::App::minimalSize() const
{
    return m_minimalSize;
}

cfg::app::MinimalSize &cfg::App::minimalSize()
{
    return EGG_REF_CAST(cfg::App, cfg::app::MinimalSize, minimalSize);
}

void cfg::App::setFontSize(double size)
{
    set("fontSize", size);
}

double cfg::App::fontSize() const
{
    return get("fontSize").toDouble();
}

void cfg::App::setLog(bool log)
{
    set("log", log);
}

bool cfg::App::log() const
{
    return get("log").toBool();
}
