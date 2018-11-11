#include "shortcutobject.hpp"

void cfg::ShortcutObject::loadObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::ShortcutObject::toObject() const
{
    return object();
}

void cfg::ShortcutObject::setDefaults()
{
    setDefault("next", "Ctrl + F12");
    setDefault("playPause", "Ctrl + F11");
    setDefault("previous", "Ctrl + F10");
    setDefault("volumeDown", "Ctrl + F7");
    setDefault("volumeUp", "Ctrl + F8");
}

void cfg::ShortcutObject::setNext(const QString &shortcut)
{
    set("next", shortcut);
}

QString cfg::ShortcutObject::next() const
{
    return get("next").toString();
}

void cfg::ShortcutObject::setPlayPause(const QString &shortcut)
{
    set("playPause", shortcut);
}

QString cfg::ShortcutObject::playPause() const
{
    return get("playPause").toString();
}

void cfg::ShortcutObject::setPrevious(const QString &shortcut)
{
    set("previous", shortcut);
}

QString cfg::ShortcutObject::previous() const
{
    return get("previous").toString();
}

void cfg::ShortcutObject::setVolumeDown(const QString &shortcut)
{
    set("volumeDown", shortcut);
}

QString cfg::ShortcutObject::volumeDown() const
{
    return get("volumeDown").toString();
}

void cfg::ShortcutObject::setVolumeUp(const QString &shortcut)
{
    set("volumeUp", shortcut);
}

QString cfg::ShortcutObject::volumeUp() const
{
    return get("volumeUp").toString();
}
