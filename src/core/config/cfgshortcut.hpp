#ifndef CFGSHORTCUT_HPP
#define CFGSHORTCUT_HPP

#include "cfgabstract.hpp"

class CfgShortcut : public CfgAbstract
{
public:
    CfgShortcut();
    CfgShortcut(QJsonObject object);

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

#endif // CFGSHORTCUT_HPP
