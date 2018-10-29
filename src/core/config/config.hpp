#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "core/config/cfgapp.hpp"
#include "core/config/cfgbar.hpp"
#include "core/config/cfglibrary.hpp"
#include "core/config/cfgplayer.hpp"
#include "core/config/cfgshortcut.hpp"

#define egg_cfg (Config::instance())

#define cfg_app (egg_cfg.app())
#define cfg_bar (egg_cfg.bar())
#define cfg_library (egg_cfg.library())
#define cfg_player (egg_cfg.player())
#define cfg_shortcut (egg_cfg.shortcut())

#define cfgApp (cfg_app)
#define cfgBar (cfg_bar)
#define cfgLibrary (cfg_library)
#define cfgPlayer (cfg_player)
#define cfgShortcut (cfg_shortcut)

class Config
{
public:
    explicit Config();
    explicit Config(const Config &) = delete;
    ~Config();

    static Config &instance();

    cfg::App &app();
    cfg::Bar &bar();
    cfg::Library &library();
    cfg::Player &player();
    cfg::Shortcut &shortcut();

    void operator=(const Config &) = delete;

private:
    void load();
    void save();
    void setDefaults();

    cfg::App m_app;
    cfg::Bar m_bar;
    cfg::Library m_library;
    cfg::Player m_player;
    cfg::Shortcut m_shortcut;
};

#endif // CONFIG_HPP
