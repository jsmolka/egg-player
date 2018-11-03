#include "cfgappminimalsize.hpp"

void cfg::app::MinimalSize::loadObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::app::MinimalSize::toObject() const
{
    return object();
}

void cfg::app::MinimalSize::setDefaults()
{
    setDefault("height", 450);
    setDefault("width", 800);
}

void cfg::app::MinimalSize::setHeight(int height)
{
    set("height", height);
}

int cfg::app::MinimalSize::height() const
{
    return get("height").toInt();
}

void cfg::app::MinimalSize::setWidth(int width)
{
    set("width", width);
}

int cfg::app::MinimalSize::width() const
{
    return get("width").toInt();
}
