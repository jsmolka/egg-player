#ifndef CFGSHORTCUT_HPP
#define CFGSHORTCUT_HPP

#include "core/config/jsonobject.hpp"

namespace cfg
{
class ShortcutObject : public JsonObject
{
public:
    void loadObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

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
}

#endif // CFGSHORTCUT_HPP
