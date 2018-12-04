#include "config.hpp"

#include <QJsonDocument>

#include "core/constants.hpp"
#include "core/macros.hpp"
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

const cfg::AppJson &Config::app() const
{
    return m_app;
}

const cfg::BarJson &Config::bar() const
{
    return m_bar;
}

const cfg::LibraryJson &Config::library() const
{
    return m_library;
}

const cfg::PlayerJson &Config::player() const
{
    return m_player;
}

const cfg::ShortcutJson &Config::shortcut() const
{
    return m_shortcut;
}

cfg::AppJson &Config::app()
{
    return EGG_REF_CAST(Config, cfg::AppJson, app);
}

cfg::BarJson &Config::bar()
{
    return EGG_REF_CAST(Config, cfg::BarJson, bar);
}

cfg::LibraryJson &Config::library()
{
    return EGG_REF_CAST(Config, cfg::LibraryJson, library);
}

cfg::PlayerJson &Config::player()
{
    return EGG_REF_CAST(Config, cfg::PlayerJson, player);
}

cfg::ShortcutJson &Config::shortcut()
{
    return EGG_REF_CAST(Config,  cfg::ShortcutJson, shortcut);
}

void Config::load()
{
    const QJsonDocument json = QJsonDocument::fromJson(FileUtil::readBytes(constants::cfg::File, "{}"));
    const QJsonObject object = json.object();

    m_app.loadFromObject(object.value("app").toObject());
    m_bar.loadFromObject(object.value("bar").toObject());
    m_library.loadFromObject(object.value("library").toObject());
    m_player.loadFromObject(object.value("player").toObject());
    m_shortcut.loadFromObject(object.value("shortcut").toObject());
}

void Config::save()
{
    QJsonObject object;
    object.insert("app", m_app.toObject());
    object.insert("bar", m_bar.toObject());
    object.insert("library", m_library.toObject());
    object.insert("player", m_player.toObject());
    object.insert("shortcut", m_shortcut.toObject());

    FileUtil::write(constants::cfg::File, QJsonDocument(object).toJson());
}

void Config::setDefaults()
{
    m_app.setDefaults();
    m_bar.setDefaults();
    m_library.setDefaults();
    m_player.setDefaults();
    m_shortcut.setDefaults();
}
