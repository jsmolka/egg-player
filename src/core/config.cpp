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

const cfg::AppObject &Config::app() const
{
    return m_app;
}

const cfg::BarObject &Config::bar() const
{
    return m_bar;
}

const cfg::LibraryObject &Config::library() const
{
    return m_library;
}

const cfg::PlayerObject &Config::player() const
{
    return m_player;
}

const cfg::ShortcutObject &Config::shortcut() const
{
    return m_shortcut;
}

cfg::AppObject &Config::app()
{
    return EGG_REF_CAST(Config, cfg::AppObject, app);
}

cfg::BarObject &Config::bar()
{
    return EGG_REF_CAST(Config, cfg::BarObject, bar);
}

cfg::LibraryObject &Config::library()
{
    return EGG_REF_CAST(Config, cfg::LibraryObject, library);
}

cfg::PlayerObject &Config::player()
{
    return EGG_REF_CAST(Config, cfg::PlayerObject, player);
}

cfg::ShortcutObject &Config::shortcut()
{
    return EGG_REF_CAST(Config,  cfg::ShortcutObject, shortcut);
}

void Config::load()
{
    const QJsonDocument json = QJsonDocument::fromJson(FileUtil::readBytes(constants::cfg::file, "{}"));
    const QJsonObject object = json.object();

    m_app.loadObject(object.value("app").toObject());
    m_bar.loadObject(object.value("bar").toObject());
    m_library.loadObject(object.value("library").toObject());
    m_player.loadObject(object.value("player").toObject());
    m_shortcut.loadObject(object.value("shortcut").toObject());
}

void Config::save()
{
    QJsonObject object;
    object.insert("app", m_app.toObject());
    object.insert("bar", m_bar.toObject());
    object.insert("library", m_library.toObject());
    object.insert("player", m_player.toObject());
    object.insert("shortcut", m_shortcut.toObject());

    QJsonDocument json;
    json.setObject(object);

    FileUtil::write(constants::cfg::file, json.toJson());
}

void Config::setDefaults()
{
    m_app.setDefaults();
    m_bar.setDefaults();
    m_library.setDefaults();
    m_player.setDefaults();
    m_shortcut.setDefaults();
}
