#include "configshortcut.hpp"

ConfigShortcut::ConfigShortcut()
{

}

ConfigShortcut::ConfigShortcut(const QJsonObject &object)
    : ConfigItem(object)
{

}

ConfigShortcut::~ConfigShortcut()
{

}

void ConfigShortcut::setDefaults()
{
    setDefault("next", "Ctrl F12");
    setDefault("playPause", "Ctrl F11");
    setDefault("previous", "Ctrl F10");
    setDefault("volumeDown", "Ctrl F7");
    setDefault("volumeUp", "Ctrl F8");
}

void ConfigShortcut::setNext(const QString &shortcut)
{
    set("next", shortcut);
}

QString ConfigShortcut::next()
{
    return get("next").toString();
}

void ConfigShortcut::setPlayPause(const QString &shortcut)
{
    set("playPause", shortcut);
}

QString ConfigShortcut::playPause()
{
    return get("playPause").toString();
}

void ConfigShortcut::setPrevious(const QString &shortcut)
{
    set("previous", shortcut);
}

QString ConfigShortcut::previous()
{
    return get("previous").toString();
}

void ConfigShortcut::setVolumeDown(const QString &shortcut)
{
    set("volumeDown", shortcut);
}

QString ConfigShortcut::volumeDown()
{
    return get("volumeDown").toString();
}

void ConfigShortcut::setVolumeUp(const QString &shortcut)
{
    set("volumeUp", shortcut);
}

QString ConfigShortcut::volumeUp()
{
    return get("volumeUp").toString();
}
