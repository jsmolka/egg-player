#include "appjson.hpp"

#include "core/macros.hpp"

void cfg::app::MinimalSizeJson::loadObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::app::MinimalSizeJson::toObject() const
{
    return object();
}

void cfg::app::MinimalSizeJson::setDefaults()
{
    setDefault("height", 450);
    setDefault("width", 800);
}

void cfg::app::MinimalSizeJson::setHeight(int height)
{
    set("height", height);
}

int cfg::app::MinimalSizeJson::height() const
{
    return get("height").toInt();
}

void cfg::app::MinimalSizeJson::setWidth(int width)
{
    set("width", width);
}

int cfg::app::MinimalSizeJson::width() const
{
    return get("width").toInt();
}

void cfg::AppJson::loadObject(const QJsonObject &object)
{
    setObject(object);

    m_minimalSize.loadObject(object.value("minimalSize").toObject());
}

QJsonObject cfg::AppJson::toObject() const
{
    QJsonObject object = this->object();
    object.insert("minimalSize", m_minimalSize.toObject());

    return object;
}

void cfg::AppJson::setDefaults()
{
    setDefault("fontSize", 10.25);
    setDefault("log", true);

    m_minimalSize.setDefaults();
}

const cfg::app::MinimalSizeJson &cfg::AppJson::minimalSize() const
{
    return m_minimalSize;
}

cfg::app::MinimalSizeJson &cfg::AppJson::minimalSize()
{
    return EGG_REF_CAST(cfg::AppJson, cfg::app::MinimalSizeJson, minimalSize);
}

void cfg::AppJson::setFontSize(double size)
{
    set("fontSize", size);
}

double cfg::AppJson::fontSize() const
{
    return get("fontSize").toDouble();
}

void cfg::AppJson::setLog(bool log)
{
    set("log", log);
}

bool cfg::AppJson::log() const
{
    return get("log").toBool();
}
