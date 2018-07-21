#include "configbar.hpp"

void ConfigBar::setDefaults()
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

void ConfigBar::setGrooveHeight(int height)
{
    set("grooveHeight", height);
}

int ConfigBar::grooveHeight()
{
    return makeEven(scale(get("grooveHeight").toInt()));
}

void ConfigBar::setHandleSize(int size)
{
    set("handleSize", size);
}

int ConfigBar::handleSize()
{
    return makeEven(scale(get("handleSize").toInt()));
}

void ConfigBar::setHeight(int height)
{
    set("height", height);
}

int ConfigBar::height()
{
    return makeEven(scale(get("height").toInt()));
}

void ConfigBar::setIconSize(int size)
{
    set("iconSize", size);
}

int ConfigBar::iconSize()
{
    return makeEven(scale(get("iconSize").toInt()));
}

void ConfigBar::setMargin(int margin)
{
    set("margin", margin);
}

int ConfigBar::margin()
{
    return scale(get("margin").toInt());
}

void ConfigBar::setSpacing(int spacing)
{
    set("spacing", spacing);
}

int ConfigBar::spacing()
{
    return scale(get("spacing").toInt());
}

int ConfigBar::coverSize()
{
    return height() - 2 * margin();
}

void ConfigBar::setTimeWidth(int width)
{
    set("timeWidth", width);
}

int ConfigBar::timeWidth()
{
    return scale(get("timeWidth").toInt());
}

void ConfigBar::setTrackWidth(int width)
{
    set("timeWidth", width);
}

int ConfigBar::trackWidth()
{
    return scale(get("trackWidth").toInt());
}
