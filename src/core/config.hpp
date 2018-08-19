#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QObject>

#include "configapp.hpp"
#include "configbar.hpp"
#include "configlibrary.hpp"
#include "configplayer.hpp"
#include "configshortcut.hpp"

#define cfgApp (Config::instance()->app())
#define cfgBar (Config::instance()->bar())
#define cfgLibrary (Config::instance()->library())
#define cfgPlayer (Config::instance()->player())
#define cfgShortcut (Config::instance()->shortcut())

class Config : QObject
{
public:
    explicit Config(QObject *parent = nullptr);
    ~Config();

    static Config *instance();

    ConfigApp &app();
    ConfigBar &bar();
    ConfigLibrary &library();
    ConfigPlayer &player();
    ConfigShortcut &shortcut();

private:
    void load();
    void save();
    void setDefaults();

    ConfigApp m_app;
    ConfigBar m_bar;
    ConfigLibrary m_library;
    ConfigPlayer m_player;
    ConfigShortcut m_shortcut;
};

#endif // CONFIG_HPP
