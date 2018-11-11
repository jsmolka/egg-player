#include "appobject.hpp"

#include "core/macros.hpp"

void cfg::app::MinimalSizeObject::loadObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::app::MinimalSizeObject::toObject() const
{
    return object();
}

void cfg::app::MinimalSizeObject::setDefaults()
{
    setDefault("height", 450);
    setDefault("width", 800);
}

void cfg::app::MinimalSizeObject::setHeight(int height)
{
    set("height", height);
}

int cfg::app::MinimalSizeObject::height() const
{
    return get("height").toInt();
}

void cfg::app::MinimalSizeObject::setWidth(int width)
{
    set("width", width);
}

int cfg::app::MinimalSizeObject::width() const
{
    return get("width").toInt();
}

void cfg::AppObject::loadObject(const QJsonObject &object)
{
    setObject(object);

    m_minimalSize.loadObject(object.value("minimalSize").toObject());
}

QJsonObject cfg::AppObject::toObject() const
{
    QJsonObject object = this->object();
    object.insert("minimalSize", m_minimalSize.toObject());

    return object;
}

void cfg::AppObject::setDefaults()
{
    setDefault("fontSize", 10.25);
    setDefault("log", true);

    m_minimalSize.setDefaults();
}

const cfg::app::MinimalSizeObject &cfg::AppObject::minimalSize() const
{
    return m_minimalSize;
}

cfg::app::MinimalSizeObject &cfg::AppObject::minimalSize()
{
    return EGG_REF_CAST(cfg::AppObject, cfg::app::MinimalSizeObject, minimalSize);
}

void cfg::AppObject::setFontSize(double size)
{
    set("fontSize", size);
}

double cfg::AppObject::fontSize() const
{
    return get("fontSize").toDouble();
}

void cfg::AppObject::setLog(bool log)
{
    set("log", log);
}

bool cfg::AppObject::log() const
{
    return get("log").toBool();
}
