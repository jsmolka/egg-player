#include "cfgshortcut.hpp"

void cfg::Shortcut::loadObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::Shortcut::toObject() const
{
    return object();
}

void cfg::Shortcut::setDefaults()
{
    setDefault("next", "Ctrl + F12");
    setDefault("playPause", "Ctrl + F11");
    setDefault("previous", "Ctrl + F10");
    setDefault("volumeDown", "Ctrl + F7");
    setDefault("volumeUp", "Ctrl + F8");
}

void cfg::Shortcut::setNext(const QString &shortcut)
{
    set("next", shortcut);
}

QString cfg::Shortcut::next() const
{
    return get("next").toString();
}

void cfg::Shortcut::setPlayPause(const QString &shortcut)
{
    set("playPause", shortcut);
}

QString cfg::Shortcut::playPause() const
{
    return get("playPause").toString();
}

void cfg::Shortcut::setPrevious(const QString &shortcut)
{
    set("previous", shortcut);
}

QString cfg::Shortcut::previous() const
{
    return get("previous").toString();
}

void cfg::Shortcut::setVolumeDown(const QString &shortcut)
{
    set("volumeDown", shortcut);
}

QString cfg::Shortcut::volumeDown() const
{
    return get("volumeDown").toString();
}

void cfg::Shortcut::setVolumeUp(const QString &shortcut)
{
    set("volumeUp", shortcut);
}

QString cfg::Shortcut::volumeUp() const
{
    return get("volumeUp").toString();
}
