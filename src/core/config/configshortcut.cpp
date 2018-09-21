#include "configshortcut.hpp"

void ConfigShortcut::setDefaults()
{
    setDefault("next", "Ctrl + F12");
    setDefault("playPause", "Ctrl + F11");
    setDefault("previous", "Ctrl + F10");
    setDefault("volumeDown", "Ctrl + F7");
    setDefault("volumeUp", "Ctrl + F8");
}

void ConfigShortcut::setNext(const QString &shortcut)
{
    set("next", shortcut);
}

QString ConfigShortcut::next() const
{
    return get("next").toString();
}

void ConfigShortcut::setPlayPause(const QString &shortcut)
{
    set("playPause", shortcut);
}

QString ConfigShortcut::playPause() const
{
    return get("playPause").toString();
}

void ConfigShortcut::setPrevious(const QString &shortcut)
{
    set("previous", shortcut);
}

QString ConfigShortcut::previous() const
{
    return get("previous").toString();
}

void ConfigShortcut::setVolumeDown(const QString &shortcut)
{
    set("volumeDown", shortcut);
}

QString ConfigShortcut::volumeDown() const
{
    return get("volumeDown").toString();
}

void ConfigShortcut::setVolumeUp(const QString &shortcut)
{
    set("volumeUp", shortcut);
}

QString ConfigShortcut::volumeUp() const
{
    return get("volumeUp").toString();
}
