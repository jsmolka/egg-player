#include "cfgapp.hpp"

void cfg::App::setDefaults()
{
    setDefault("fontSize", 10.25);
    setDefault("log", true);
    setDefault("minimalHeight", 450);
    setDefault("minimalWidth", 800);
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

void cfg::App::setMinimalHeight(int height)
{
    set("minimalHeight", height);
}

int cfg::App::minimalHeight() const
{
    return scale(get("minimalHeight").toInt());
}

void cfg::App::setMinimalWidth(int width)
{
    set("minimalWidth", width);
}

int cfg::App::minimalWidth() const
{
    return scale(get("minimalWidth").toInt());
}
