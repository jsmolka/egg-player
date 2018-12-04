#include "shortcutjson.hpp"

void cfg::ShortcutJson::loadFromObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::ShortcutJson::toObject() const
{
    return object();
}

void cfg::ShortcutJson::setDefaults()
{
    setDefault("next", "Ctrl + F12");
    setDefault("playPause", "Ctrl + F11");
    setDefault("previous", "Ctrl + F10");
    setDefault("volumeDown", "Ctrl + F7");
    setDefault("volumeStep", 2);
    setDefault("volumeUp", "Ctrl + F8");
}

void cfg::ShortcutJson::setNext(const QString &shortcut)
{
    set("next", shortcut);
}

QString cfg::ShortcutJson::next() const
{
    return get("next").toString();
}

void cfg::ShortcutJson::setPlayPause(const QString &shortcut)
{
    set("playPause", shortcut);
}

QString cfg::ShortcutJson::playPause() const
{
    return get("playPause").toString();
}

void cfg::ShortcutJson::setPrevious(const QString &shortcut)
{
    set("previous", shortcut);
}

QString cfg::ShortcutJson::previous() const
{
    return get("previous").toString();
}

void cfg::ShortcutJson::setVolumeDown(const QString &shortcut)
{
    set("volumeDown", shortcut);
}

QString cfg::ShortcutJson::volumeDown() const
{
    return get("volumeDown").toString();
}

void cfg::ShortcutJson::setVolumeStep(int step)
{
    set("volumeStep", step);
}

int cfg::ShortcutJson::volumeStep() const
{
    return get("volumeStep").toInt();
}

void cfg::ShortcutJson::setVolumeUp(const QString &shortcut)
{
    set("volumeUp", shortcut);
}

QString cfg::ShortcutJson::volumeUp() const
{
    return get("volumeUp").toString();
}
