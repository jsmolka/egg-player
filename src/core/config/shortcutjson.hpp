#ifndef CFG_SHORTCUTJSON_HPP
#define CFG_SHORTCUTJSON_HPP

#include "core/config/jsonobject.hpp"

namespace cfg
{

class ShortcutJson : public JsonObject
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

    void setVolumeStep(int step);
    int volumeStep() const;

    void setVolumeUp(const QString &shortcut);
    QString volumeUp() const;
};

}

#endif // CFG_SHORTCUTJSON_HPP
