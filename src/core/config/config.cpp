#include "config.hpp"

Config::Config(QObject *parent)
    : QObject(parent)
{
    QJsonDocument json = QJsonDocument::fromJson("{}");
    if (FileUtil::exists(CFG_PATH))
    {
        QFile file(CFG_PATH);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            json = QJsonDocument::fromJson(file.readAll());
    }

    app = CfgApp(json.object().value("app").toObject());
    bar = CfgBar(json.object().value("bar").toObject());
    library = CfgLibrary(json.object().value("library").toObject());
    player = CfgPlayer(json.object().value("player").toObject());
    shortcut = CfgShortcut(json.object().value("shortcut").toObject());

    app.setDefaults();
    bar.setDefaults();
    library.setDefaults();
    player.setDefaults();
    shortcut.setDefaults();
}

Config::~Config()
{
    QJsonDocument json = QJsonDocument::fromJson("{}");
    QJsonObject object = json.object();
    object.insert("app", app.object());
    object.insert("bar", bar.object());
    object.insert("library", library.object());
    object.insert("player", player.object());
    object.insert("shortcut", shortcut.object());
    json.setObject(object);

    QFile file(CFG_PATH);
    if (file.open(QFile::WriteOnly))
        file.write(json.toJson());
}

Config * Config::instance()
{
    if (!_instance)
        _instance = new Config(qApp);

    return _instance;
}

Config * Config::_instance = nullptr;
