#include "config.hpp"

Config::Config(QObject *parent)
    : QObject(parent)
{
    load();

    setDefaults();
}

Config::~Config()
{
    save();
}

Config * Config::instance()
{
    static Config *config = new Config(qApp);
    return config;
}

ConfigApp * Config::app()
{
    return &m_app;
}

ConfigBar * Config::bar()
{
    return &m_bar;
}

ConfigLibrary * Config::library()
{
    return &m_library;
}

ConfigPlayer * Config::player()
{
    return &m_player;
}

ConfigShortcut * Config::shortcut()
{
    return &m_shortcut;
}

void Config::load()
{
    QJsonDocument json = QJsonDocument::fromJson(FileUtil::readBytes(CFG_PATH, "{}"));

    QJsonObject object = json.object();
    m_app = ConfigApp(object.value("app").toObject());
    m_bar = ConfigBar(object.value("bar").toObject());
    m_library = ConfigLibrary(object.value("library").toObject());
    m_player = ConfigPlayer(object.value("player").toObject());
    m_shortcut = ConfigShortcut(object.value("shortcut").toObject());
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
