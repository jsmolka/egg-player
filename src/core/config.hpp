#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "core/singleton.hpp"
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

class Config : public Singleton<Config>
{
public:
    Config();
    ~Config();

    const cfg::App &app() const;
    const cfg::Bar &bar() const;
    const cfg::Library &library() const;
    const cfg::Player &player() const;
    const cfg::Shortcut &shortcut() const;

    cfg::App &app();
    cfg::Bar &bar();
    cfg::Library &library();
    cfg::Player &player();
    cfg::Shortcut &shortcut();

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
