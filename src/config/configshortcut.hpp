#ifndef CONFIGSHORTCUT_HPP
#define CONFIGSHORTCUT_HPP

#include "configitem.hpp"

/*!
 * Represents a shortcut item.
 */
class ConfigShortcut : public ConfigItem
{
public:
    /*!
     * Constructor.
     */
    ConfigShortcut();
    /*!
     * Constructor.
     */
    ConfigShortcut(const QJsonObject &object);
    /*!
     * Destructor.
     */
    ~ConfigShortcut();
    /*!
     * Sets defaults.
     */
    void setDefaults() override;
    /*!
     * Setter for next shortcut.
     */
    void setNext(const QString &shortcut);
    /*!
     * Getter for next shortcut.
     */
    QString next();
    /*!
     * Setter for play pause shortcut.
     */
    void setPlayPause(const QString &shortcut);
    /*!
     * Getter for play pause shortcut.
     */
    QString playPause();
    /*!
     * Setter for previous shortcut.
     */
    void setPrevious(const QString &shortcut);
    /*!
     * Getter for previous shortcut.
     */
    QString previous();
    /*!
     * Setter for volume down shortcut.
     */
    void setVolumeDown(const QString &shortcut);
    /*!
     * Getter for volume down shortcut.
     */
    QString volumeDown();
    /*!
     * Setter for volume up shortcut.
     */
    void setVolumeUp(const QString &shortcut);
    /*!
     * Getter for volume up shortcut.
     */
    QString volumeUp();
};

#endif // CONFIGSHORTCUT_HPP
