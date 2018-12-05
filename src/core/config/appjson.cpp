#include "appjson.hpp"

#include "core/macros.hpp"

void cfg::MinimalSizeJson::loadFromObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::MinimalSizeJson::toObject() const
{
    return object();
}

void cfg::MinimalSizeJson::setDefaults()
{
    setDefault("height", 450);
    setDefault("width", 800);
}

void cfg::MinimalSizeJson::setHeight(int height)
{
    set("height", height);
}

int cfg::MinimalSizeJson::height() const
{
    return get("height").toInt();
}

void cfg::MinimalSizeJson::setWidth(int width)
{
    set("width", width);
}

int cfg::MinimalSizeJson::width() const
{
    return get("width").toInt();
}

void cfg::AppJson::loadFromObject(const QJsonObject &object)
{
    setObject(object);

    m_minimalSize.loadFromObject(object.value("minimalSize").toObject());
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

    m_minimalSize.setDefaults();
}

const cfg::MinimalSizeJson &cfg::AppJson::minimalSize() const
{
    return m_minimalSize;
}

cfg::MinimalSizeJson &cfg::AppJson::minimalSize()
{
    return EGG_REF_CAST(cfg::AppJson, cfg::MinimalSizeJson, minimalSize);
}

void cfg::AppJson::setFontSize(double size)
{
    set("fontSize", size);
}

double cfg::AppJson::fontSize() const
{
    return get("fontSize").toDouble();
}
