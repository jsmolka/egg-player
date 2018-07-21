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

class Config : QObject
{
public:
    Config(QObject *parent = nullptr);
    ~Config();

    static Config * instance();

    ConfigApp * app();
    ConfigBar * bar();
    ConfigLibrary * library();
    ConfigPlayer * player();
    ConfigShortcut * shortcut();

private:
    void load();
    void save();

    ConfigApp m_app;
    ConfigBar m_bar;
    ConfigLibrary m_library;
    ConfigPlayer m_player;
    ConfigShortcut m_shortcut;

    static Config *_instance;
};

#endif // CONFIG_HPP
