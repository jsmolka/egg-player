#include "cfgbarlabelwidth.hpp"

void cfg::bar::LabelWidth::loadObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::bar::LabelWidth::toObject() const
{
    return object();
}

void cfg::bar::LabelWidth::setDefaults()
{
    setDefault("time", 50);
    setDefault("track", 240);
}

void cfg::bar::LabelWidth::setTime(int width)
{
    set("time", width);
}

int cfg::bar::LabelWidth::time() const
{
    return scale(get("time").toInt());
}

void cfg::bar::LabelWidth::setTrack(int width)
{
    set("time", width);
}

int cfg::bar::LabelWidth::track() const
{
    return scale(get("track").toInt());
}
