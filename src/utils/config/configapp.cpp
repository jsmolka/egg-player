#include "configapp.hpp"

ConfigApp::ConfigApp()
{

}

ConfigApp::ConfigApp(const QJsonObject &object)
    : ConfigItem(object)
{

}

ConfigApp::~ConfigApp()
{

}

void ConfigApp::setDefaults()
{
    setDefault("fontSize", 10.25);
    setDefault("log", true);
}

void ConfigApp::setFontSize(double size)
{
    set("fontSize", size);
}

double ConfigApp::fontSize()
{
    return get("fontSize").toDouble();
}

void ConfigApp::setLog(bool log)
{
    set("log", log);
}

bool ConfigApp::log()
{
    return get("log").toBool();
}
