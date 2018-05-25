#include "config.hpp"

/*
 * Setter for app font size.
 *
 * :param size: size
 */
void Config::App::setFontSize(double size)
{
    setValue(app(), "fontSize", size);
}

/*
 * Getter for app font size.
 *
 * :return: size
 */
double Config::App::fontSize()
{
    return app()["fontSize"].toDouble();
}

/*
 * Setter for app log.
 *
 * :param log: log
 */
void Config::App::setLog(bool log)
{
    setValue(app(), "log", log);
}

/*
 * Getter for app log.
 *
 * :return: log
 */
bool Config::App::log()
{
    return app()["log"].toBool();
}

/*
 * Setter for groove height.
 *
 * :param height: height
 */
void Config::Bar::setGrooveHeight(int height)
{
    setValue(bar(), "grooveHeight", height);
}

/*
 * Getter for groove height.
 *
 * :return: height
 */
int Config::Bar::grooveHeight()
{
    return makeEven(scale(bar()["grooveHeight"].toInt()));
}

/*
 * Setter for handle size.
 *
 * :param size: size
 */
void Config::Bar::setHandleSize(int size)
{
    setValue(bar(), "handleSize", size);
}

/*
 * Getter for groove height.
 *
 * :return height
 */
int Config::Bar::handleSize()
{
    return  makeEven(scale(bar()["handleSize"].toInt()));
}

/*
 * Setter for bar height.
 *
 * :param height: height
 */
void Config::Bar::setHeight(int height)
{
    setValue(bar(), "height", height);
}

/*
 * Getter for bar height.
 *
 * :result: height
 */
int Config::Bar::height()
{
    return makeEven(scale(bar()["height"].toInt()));
}

/*
 * Setter for bar icon size.
 *
 * :param size: size
 */
void Config::Bar::setIconSize(int size)
{
    setValue(bar(), "iconSize", size);
}

/*
 * Getter for bar icon size.
 *
 * :return: size
 */
int Config::Bar::iconSize()
{
    return makeEven(scale(bar()["iconSize"].toInt()));
}

/*
 * Setter for bar margin.
 *
 * :param margin: margin
 */
void Config::Bar::setMargin(int margin)
{
    setValue(bar(), "margin", margin);
}

/*
 * Getter for bar margin.
 *
 * :return: margin
 */
int Config::Bar::margin()
{
    return scale(bar()["margin"].toInt());
}

/*
 * Setter for bar spacing.
 *
 * :param spacing: spacing
 */
void Config::Bar::setSpacing(int spacing)
{
    setValue(bar(), "spacing", spacing);
}

/*
 * Getter for bar spacing.
 *
 * :return: spacing
 */
int Config::Bar::spacing()
{
    return scale(bar()["spacing"].toInt());
}

/*
 * Getter for bar cover size.
 *
 * :return: size
 */
int Config::Bar::coverSize()
{
    return Bar::height() - 2 * Bar::margin();
}

/*
 * Setter for bar time width.
 *
 * :param width: width
 */
void Config::Bar::setTimeWidth(int width)
{
    setValue(bar(), "timeWidth", width);
}

/*
 * Getter for bar time width.
 *
 * :return: width
 */
int Config::Bar::timeWidth()
{
    return scale(bar()["timeWidth"].toInt());
}

/*
 * Setter for bar track width.
 *
 * :param width: width
 */
void Config::Bar::setTrackWidth(int width)
{
    setValue(bar(), "timeWidth", width);
}

/*
 * Getter for bar track width.
 *
 * :return: width
 */
int Config::Bar::trackWidth()
{
    return scale(bar()["trackWidth"].toInt());
}

/*
 * Setter for cell padding.
 *
 * :param padding: padding
 */
void Config::Library::setCellPadding(int padding)
{
    setValue(library(), "cellPadding", padding);
}

/*
 * Getter for cell padding.
 *
 * :return: padding
 */
int Config::Library::cellPadding()
{
    return scale(library()["cellPadding"].toInt());
}

/*
 * Setter for library item height.
 *
 * :param height: height
 */
void Config::Library::setItemHeight(int height)
{
    setValue(library(), "itemHeight", height);
}

/*
 * Getter for library item height.
 *
 * :return: height
 */
int Config::Library::itemHeight()
{
    return scale(library()["itemHeight"].toInt());
}

/*
 * Setter for library paths.
 *
 * :param string: paths
 */
void Config::Library::setPaths(const StringList &paths)
{
    QJsonArray array;
    for (const QString &path : paths)
        array << QJsonValue::fromVariant(path);

    setValue(library(), "paths", QJsonValue(array));
}

/*
 * Getter for library paths.
 *
 * :return: path
 */
StringList Config::Library::paths()
{
    StringList list;
    for (const QJsonValue &element : library()["paths"].toArray())
        list << element.toString();

    return list;
}

/*
 * Setter for scroll bar width.
 *
 * :param width: width
 */
void Config::Library::setScrollBarWidth(int width)
{
    setValue(library(), "scrollBarWidth", width);
}

/*
 * Getter for scroll bar width.
 *
 * :return: width
 */
int Config::Library::scrollBarWidth()
{
    return scale(library()["scrollBarWidth"].toInt());
}

/*
 * Setter for player loop.
 *
 * :param loop: loop
 */
void Config::Player::setLoop(bool loop)
{
    setValue(player(), "loop", loop);
}

/*
 * Getter for player loop.
 *
 * :return: loop
 */
bool Config::Player::loop()
{
    return player()["loop"].toBool();
}

/*
 * Setter for player shuffle.
 *
 * :param shuffle: shuffle
 */
void Config::Player::setShuffle(bool shuffle)
{
    setValue(player(), "shuffle", shuffle);
}

/*
 * Getter for player shuffle.
 *
 * :return: shuffle
 */
bool Config::Player::shuffle()
{
    return player()["shuffle"].toBool();
}

/*
 * Setter for player volume.
 *
 * :param volume: volume
 */
void Config::Player::setVolume(int volume)
{
    setValue(player(), "volume", volume);
}

/*
 * Getter for player volume.
 *
 * :return: volume
 */
int Config::Player::volume()
{
    return player()["volume"].toInt();
}

/*
 * Setter for next shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setNext(const QString &shortcut)
{
    setValue(Config::shortcut(), "next", shortcut);
}

/*
 * Getter for next shortcut.
 *
 * :return: shortcut
 */
QString Config::Shortcut::next()
{
    return shortcut()["next"].toString();
}

/*
 * Setter for play pause shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setPlayPause(const QString &shortcut)
{
    setValue(Config::shortcut(), "playPause", shortcut);
}

/*
 * Getter for play pause shortcut.
 *
 * :return: shortcut
 */
QString Config::Shortcut::playPause()
{
    return shortcut()["playPause"].toString();
}

/*
 * Setter for previous shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setPrevious(const QString &shortcut)
{
    setValue(Config::shortcut(), "previous", shortcut);
}

/*
 * Getter for previous shortcut.
 *
 * :return: shortcut
 */
QString Config::Shortcut::previous()
{
    return shortcut()["previous"].toString();
}

/*
 * Setter for volume down shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setVolumeDown(const QString &shortcut)
{
    setValue(Config::shortcut(), "volumeDown", shortcut);
}

/*
 * Getter for volume down shortcut.
 *
 * :return: shortcut
 */
QString Config::Shortcut::volumeDown()
{
    return shortcut()["volumeDown"].toString();
}

/*
 * Setter for volume up shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setVolumeUp(const QString &shortcut)
{
    setValue(Config::shortcut(), "volumeUp", shortcut);
}

/*
 * Getter for volume up shortcut.
 *
 * :return: shortcut
 */
QString Config::Shortcut::volumeUp()
{
    return shortcut()["volumeUp"].toString();
}

/*
 * Saves objects.
 */
void Config::saveObjects()
{
    QJsonObject object = _json.object();
    object["app"] = _app;
    object["bar"] = _bar;
    object["library"] = _library;
    object["player"] = _player;
    object["shortcut"] = _shortcut;
    _json.setObject(object);
}

/*
 * Loads objects.
 */
void Config::loadObjects()
{
    QJsonObject object = _json.object();
    _app = object["app"].toObject();
    _bar = object["bar"].toObject();
    _library = object["library"].toObject();
    _player = object["player"].toObject();
    _shortcut = object["shortcut"].toObject();
}

/*
 * Saves the made changes by writing it to the file.
 */
void Config::save()
{
    saveObjects();

    QFile file(CFG_PATH);
    if (file.open(QFile::WriteOnly))
        file.write(_json.toJson());
}

/*
 * Reads or creates the config file.
 */
void Config::load()
{
    if (FileUtil::exists(CFG_PATH))
    {
        QFile file(CFG_PATH);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            _json = QJsonDocument::fromJson(file.readAll());
    }
    else
    {
        _json = QJsonDocument::fromJson("{}");
    }

    loadObjects();
    setDefaults();
}

/*
 * Loads the json file if it does not exist.
 */
void Config::checkJson()
{
    if (_json.isNull())
        load();
}

/*
 * Gets the app object.
 *
 * :return: app
 */
QJsonObject & Config::app()
{
    checkJson();
    return _app;
}

/*
 * Gets the bar object.
 *
 * :return: bar
 */
QJsonObject & Config::bar()
{
    checkJson();
    return _bar;
}

/*
 * Gets library object.
 *
 * :return: library
 */
QJsonObject & Config::library()
{
    checkJson();
    return _library;
}

/*
 * Gets player object.
 *
 * :return: player
 */
QJsonObject & Config::player()
{
    checkJson();
    return _player;
}

/*
 * Gets shortcut object.
 *
 * :return shortcut
 */
QJsonObject & Config::shortcut()
{
    checkJson();
    return _shortcut;
}

/*
 * Sets the value at key and saves changes.
 *
 * :param object: object
 * :param key: key
 * :param value: value
 */
void Config::setValue(QJsonObject &object, const QString &key, const QJsonValue &value)
{
    object[key] = value;
    save();
}

/*
 * Sets value if the key does not exist.
 *
 * :param object: object
 * :param key: key
 * :param value: value
 */
void Config::setDefault(QJsonObject &object, const QString &key, const QJsonValue &value)
{
    if (!object.contains(key))
        setValue(object, key, value);
}

/*
 * Sets all default values.
 */
void Config::setDefaults()
{
    setDefault(app(), "fontSize", 10.25);
    setDefault(app(), "log", true);

    setDefault(bar(), "grooveHeight", 2);
    setDefault(bar(), "handleSize", 16);
    setDefault(bar(), "height", 68);
    setDefault(bar(), "iconSize", 32);
    setDefault(bar(), "margin", 8);
    setDefault(bar(), "spacing", 8);
    setDefault(bar(), "timeWidth", 50);
    setDefault(bar(), "trackWidth", 240);

    setDefault(library(), "cellPadding", 5);
    setDefault(library(), "itemHeight", 50);
    setDefault(library(), "paths", QJsonValue(QJsonArray({QStandardPaths::writableLocation(QStandardPaths::MusicLocation)})));
    setDefault(library(), "scrollBarWidth", 12);

    setDefault(player(), "loop", false);
    setDefault(player(), "shuffle", false);
    setDefault(player(), "volume", 25);

    setDefault(shortcut(), "next", "Ctrl F12");
    setDefault(shortcut(), "playPause", "Ctrl F11");
    setDefault(shortcut(), "previous", "Ctrl F10");
    setDefault(shortcut(), "volumeDown", "Ctrl F7");
    setDefault(shortcut(), "volumeUp", "Ctrl F8");
}

/*
 * Scales value.
 *
 * :param value: value
 * :return: scaled value
 */
float Config::scale(float value)
{
    return (GetScaleFactorForDevice(DEVICE_PRIMARY) / 100.0) * value;
}

/*
 * Scales value.
 *
 * :param value: value
 * :return: scaled value
 */
int Config::scale(int value)
{
    return static_cast<int>(scale(static_cast<float>(value)));
}

/*
 * Makes a value even to prevent user interface alignment problems.
 *
 * :param value: value
 * :return even: value
 */
int Config::makeEven(int value)
{
    return value % 2 == 0 ? value : --value;
}

/*
 * Json document.
 */
QJsonDocument Config::_json;

/*
 * Json objects.
 */
QJsonObject Config::_app;
QJsonObject Config::_bar;
QJsonObject Config::_library;
QJsonObject Config::_player;
QJsonObject Config::_shortcut;
