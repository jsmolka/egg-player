#ifndef CONFIGSHORTCUT_HPP
#define CONFIGSHORTCUT_HPP

#include "configitem.hpp"

class ConfigShortcut : public ConfigItem
{
public:
    using ConfigItem::ConfigItem;

    void setDefaults() override;

    void setNext(const QString &shortcut);
    QString next();

    void setPlayPause(const QString &shortcut);
    QString playPause();

    void setPrevious(const QString &shortcut);
    QString previous();

    void setVolumeDown(const QString &shortcut);
    QString volumeDown();

    void setVolumeUp(const QString &shortcut);
    QString volumeUp();
};

#endif // CONFIGSHORTCUT_HPP
