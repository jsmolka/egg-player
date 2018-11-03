#include "cfgbarslider.hpp"

void cfg::bar::Slider::loadObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::bar::Slider::toObject() const
{
    return object();
}

void cfg::bar::Slider::setDefaults()
{
    setDefault("grooveHeight", 2);
    setDefault("handleSize", 16);
}

void cfg::bar::Slider::setGrooveHeight(int height)
{
    set("grooveHeight", height);
}

int cfg::bar::Slider::grooveHeight() const
{
    return scale(get("grooveHeight").toInt());
}

void cfg::bar::Slider::setHandleSize(int size)
{
    set("handleSize", size);
}

int cfg::bar::Slider::handleSize() const
{
    return scale(get("handleSize").toInt());
}
