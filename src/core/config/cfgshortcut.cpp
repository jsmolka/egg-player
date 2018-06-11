#include "cfgshortcut.hpp"

CfgShortcut::CfgShortcut()
{

}

CfgShortcut::CfgShortcut(QJsonObject object)
    : CfgAbstract(object)
{

}

void CfgShortcut::setDefaults()
{
    setDefault("next", "Ctrl F12");
    setDefault("playPause", "Ctrl F11");
    setDefault("previous", "Ctrl F10");
    setDefault("volumeDown", "Ctrl F7");
    setDefault("volumeUp", "Ctrl F8");
}

void CfgShortcut::setNext(const QString &shortcut)
{
    m_object.insert("next", shortcut);
}

QString CfgShortcut::next()
{
    return m_object.value("next").toString();
}

void CfgShortcut::setPlayPause(const QString &shortcut)
{
    m_object.insert("playPause", shortcut);
}

QString CfgShortcut::playPause()
{
    return m_object.value("playPause").toString();
}

void CfgShortcut::setPrevious(const QString &shortcut)
{
    m_object.insert("previous", shortcut);
}

QString CfgShortcut::previous()
{
    return m_object.value("previous").toString();
}

void CfgShortcut::setVolumeDown(const QString &shortcut)
{
    m_object.insert("volumeDown", shortcut);
}

QString CfgShortcut::volumeDown()
{
    return m_object.value("volumeDown").toString();
}

void CfgShortcut::setVolumeUp(const QString &shortcut)
{
    m_object.insert("volumeUp", shortcut);
}

QString CfgShortcut::volumeUp()
{
    return m_object.value("volumeUp").toString();
}
