#include "config.hpp"

Config::Config(QObject *parent)
    : QObject(parent)
{
    load();
}

Config::~Config()
{
    save();
}

Config * Config::instance()
{
    if (!_instance)
        _instance = new Config(qApp);

    return _instance;
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
    QJsonDocument json = QJsonDocument::fromJson("{}");
    if (FileUtil::exists(CFG_PATH))
    {
        QFile file(CFG_PATH);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            json = QJsonDocument::fromJson(file.readAll());
    }

    QJsonObject object = json.object();
    m_app = ConfigApp(object.value("app").toObject());
    m_bar = ConfigBar(object.value("bar").toObject());
    m_library = ConfigLibrary(object.value("library").toObject());
    m_player = ConfigPlayer(object.value("player").toObject());
    m_shortcut = ConfigShortcut(object.value("shortcut").toObject());

    m_app.setDefaults();
    m_bar.setDefaults();
    m_library.setDefaults();
    m_player.setDefaults();
    m_shortcut.setDefaults();
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

    QFile file(CFG_PATH);
    if (file.open(QFile::WriteOnly))
        file.write(json.toJson());
}

Config * Config::_instance = nullptr;
