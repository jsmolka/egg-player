#include "configapp.hpp"

void ConfigApp::setDefaults()
{
    setDefault("fontSize", 10.25);
    setDefault("log", true);
    setDefault("minimalHeight", 450);
    setDefault("minimalWidth", 800);
}

void ConfigApp::setFontSize(double size)
{
    set("fontSize", size);
}

double ConfigApp::fontSize() const
{
    return get("fontSize").toDouble();
}

void ConfigApp::setLog(bool log)
{
    set("log", log);
}

bool ConfigApp::log() const
{
    return get("log").toBool();
}

void ConfigApp::setMinimalHeight(int height)
{
    set("minimalHeight", height);
}

int ConfigApp::minimalHeight() const
{
    return scale(get("minimalHeight").toInt());
}

void ConfigApp::setMinimalWidth(int width)
{
    set("minimalWidth", width);
}

int ConfigApp::minimalWidth() const
{
    return scale(get("minimalWidth").toInt());
}
