#include "cfgbar.hpp"

void cfg::Bar::setDefaults()
{
    setDefault("grooveHeight", 2);
    setDefault("handleSize", 16);
    setDefault("height", 68);
    setDefault("iconSize", 32);
    setDefault("margin", 8);
    setDefault("spacing", 10);
    setDefault("timeWidth", 50);
    setDefault("trackWidth", 240);
}

void cfg::Bar::setGrooveHeight(int height)
{
    set("grooveHeight", height);
}

int cfg::Bar::grooveHeight() const
{
    return scale(get("grooveHeight").toInt());
}

void cfg::Bar::setHandleSize(int size)
{
    set("handleSize", size);
}

int cfg::Bar::handleSize() const
{
    return scale(get("handleSize").toInt());
}

void cfg::Bar::setHeight(int height)
{
    set("height", height);
}

int cfg::Bar::height() const
{
    return scale(get("height").toInt());
}

void cfg::Bar::setIconSize(int size)
{
    set("iconSize", size);
}

int cfg::Bar::iconSize() const
{
    return scale(get("iconSize").toInt());
}

void cfg::Bar::setMargin(int margin)
{
    set("margin", margin);
}

int cfg::Bar::margin() const
{
    return scale(get("margin").toInt());
}

void cfg::Bar::setSpacing(int spacing)
{
    set("spacing", spacing);
}

int cfg::Bar::spacing() const
{
    return scale(get("spacing").toInt());
}

void cfg::Bar::setTimeWidth(int width)
{
    set("timeWidth", width);
}

int cfg::Bar::timeWidth() const
{
    return scale(get("timeWidth").toInt());
}

void cfg::Bar::setTrackWidth(int width)
{
    set("timeWidth", width);
}

int cfg::Bar::trackWidth() const
{
    return scale(get("trackWidth").toInt());
}

int cfg::Bar::coverSize() const
{
    return height() - 2 * margin();
}
