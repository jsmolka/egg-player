#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "core/singleton.hpp"
#include "core/config/appobject.hpp"
#include "core/config/barobject.hpp"
#include "core/config/libraryobject.hpp"
#include "core/config/playerobject.hpp"
#include "core/config/shortcutobject.hpp"

#define cfg_app (Config::instance().app())
#define cfg_bar (Config::instance().bar())
#define cfg_library (Config::instance().library())
#define cfg_player (Config::instance().player())
#define cfg_shortcut (Config::instance().shortcut())

class Config : public Singleton<Config>
{
public:
    Config();
    ~Config();

    const cfg::AppObject &app() const;
    const cfg::BarObject &bar() const;
    const cfg::LibraryObject &library() const;
    const cfg::PlayerObject &player() const;
    const cfg::ShortcutObject &shortcut() const;

    cfg::AppObject &app();
    cfg::BarObject &bar();
    cfg::LibraryObject &library();
    cfg::PlayerObject &player();
    cfg::ShortcutObject &shortcut();

private:
    void load();
    void save();
    void setDefaults();

    cfg::AppObject m_app;
    cfg::BarObject m_bar;
    cfg::LibraryObject m_library;
    cfg::PlayerObject m_player;
    cfg::ShortcutObject m_shortcut;
};

#endif // CONFIG_HPP
