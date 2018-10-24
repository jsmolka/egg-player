#ifndef CONFIGSHORTCUT_HPP
#define CONFIGSHORTCUT_HPP

#include "core/config/configitem.hpp"

class ConfigShortcut : public ConfigItem
{
public:
    using ConfigItem::ConfigItem;

    void setDefaults() override;

    void setNext(const QString &shortcut);
    QString next() const;

    void setPlayPause(const QString &shortcut);
    QString playPause() const;

    void setPrevious(const QString &shortcut);
    QString previous() const;

    void setVolumeDown(const QString &shortcut);
    QString volumeDown() const;

    void setVolumeUp(const QString &shortcut);
    QString volumeUp() const;
};

#endif // CONFIGSHORTCUT_HPP
