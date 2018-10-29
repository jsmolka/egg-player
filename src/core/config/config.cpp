#include "config.hpp"

#include <QJsonDocument>

#include "core/constants.hpp"
#include "core/utils.hpp"

Config::Config()
{
    load();

    setDefaults();
}

Config::~Config()
{
    save();
}

Config &Config::instance()
{
    static Config config;

    return config;
}

cfg::App &Config::app()
{
    return m_app;
}

cfg::Bar &Config::bar()
{
    return m_bar;
}

cfg::Library &Config::library()
{
    return m_library;
}

cfg::Player &Config::player()
{
    return m_player;
}

cfg::Shortcut &Config::shortcut()
{
    return m_shortcut;
}

void Config::load()
{
    const QJsonDocument json = QJsonDocument::fromJson(FileUtil::readBytes(CFG_PATH, "{}"));
    const QJsonObject object = json.object();

    m_app = cfg::App(object.value("app").toObject());
    m_bar = cfg::Bar(object.value("bar").toObject());
    m_library = cfg::Library(object.value("library").toObject());
    m_player = cfg::Player(object.value("player").toObject());
    m_shortcut = cfg::Shortcut(object.value("shortcut").toObject());
}

void Config::save()
{
    QJsonDocument json = QJsonDocument::fromJson("{}");

    QJsonObject object = json.object();
    object.insert("app", m_app.object());
    object.insert("bar", m_bar.object());
    object.insert("library", m_library.object());
    object.insert("player", m_player.object());
    object.insert("shortcut", m_shortcut.object());
    json.setObject(object);

    FileUtil::write(CFG_PATH, json.toJson());
}

void Config::setDefaults()
{
    m_app.setDefaults();
    m_bar.setDefaults();
    m_library.setDefaults();
    m_player.setDefaults();
    m_shortcut.setDefaults();
}
