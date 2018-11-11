#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "core/singleton.hpp"
#include "core/config/appjson.hpp"
#include "core/config/barjson.hpp"
#include "core/config/libraryjson.hpp"
#include "core/config/playerjson.hpp"
#include "core/config/shortcutjson.hpp"

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

    const cfg::AppJson &app() const;
    const cfg::BarJson &bar() const;
    const cfg::LibraryJson &library() const;
    const cfg::PlayerJson &player() const;
    const cfg::ShortcutJson &shortcut() const;

    cfg::AppJson &app();
    cfg::BarJson &bar();
    cfg::LibraryJson &library();
    cfg::PlayerJson &player();
    cfg::ShortcutJson &shortcut();

private:
    void load();
    void save();
    void setDefaults();

    cfg::AppJson m_app;
    cfg::BarJson m_bar;
    cfg::LibraryJson m_library;
    cfg::PlayerJson m_player;
    cfg::ShortcutJson m_shortcut;
};

#endif // CONFIG_HPP
