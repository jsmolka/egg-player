#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QApplication>
#include <QJsonDocument>

#include "configapp.hpp"
#include "configbar.hpp"
#include "configlibrary.hpp"
#include "configplayer.hpp"
#include "configshortcut.hpp"
#include "constants.hpp"
#include "fileutil.hpp"

#define cfgApp (Config::instance()->app())
#define cfgBar (Config::instance()->bar())
#define cfgLibrary (Config::instance()->library())
#define cfgPlayer (Config::instance()->player())
#define cfgShortcut (Config::instance()->shortcut())

/*!
 * Represents a config.
 */
class Config : QObject
{
public:
    /*!
     * Constructor.
     */
    Config(QObject *parent = nullptr);
    /*!
     * Destructor.
     */
    ~Config();
    /*!
     * Returns the global instance.
     */
    static Config * instance();
    /*!
     * Getter for app property.
     */
    ConfigApp * app();
    /*!
     * Getter for bar property.
     */
    ConfigBar * bar();
    /*!
     * Getter for library property.
     */
    ConfigLibrary * library();
    /*!
     * Getter for player property.
     */
    ConfigPlayer * player();
    /*!
     * Getter for shortcut property.
     */
    ConfigShortcut * shortcut();

private:
    /*!
     * Member variables.
     */
    ConfigApp m_app;
    ConfigBar m_bar;
    ConfigLibrary m_library;
    ConfigPlayer m_player;
    ConfigShortcut m_shortcut;
    /*!
     * Static variables.
     */
    static Config *_instance;
};

#endif // CONFIG_HPP
