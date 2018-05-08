#include "config.hpp"

/*
 * Loads the json file and sets all default
 * values.
 */
void Config::create()
{
    load();

    App::create();
    Bar::create();
    Library::create();
    Player::create();
    Shortcut::create();
}

/*
 * Sets all non existing keys to their default
 * value.
 */
void Config::App::create()
{
    setDefault(kFontSize, dFontSize);
    setDefault(kLog, dLog);
}

/*
 * Setter for app font size.
 *
 * :param size: size
 */
void Config::App::setFontSize(double size)
{
    setValue(kFontSize, size);
}

/*
 * Getter for app font size.
 *
 * :return: size
 */
double Config::App::fontSize()
{
    return oApp[kFontSize].toDouble();
}

/*
 * Setter for app log.
 *
 * :param log: log
 */
void Config::App::setLog(bool log)
{
    setValue(kLog, log);
}

/*
 * Getter for app log.
 *
 * :return: log
 */
bool Config::App::log()
{
    return oApp[kLog].toBool();
}

/*
 * Sets non existing key to its default.
 *
 * :param key: key
 * :param value: value
 */
void Config::App::setDefault(const QString &key, const QJsonValue &value)
{
    if (!oApp.contains(key))
        setValue(key, value);
}

/*
 * Sets value at key.
 *
 * :param key: key
 * :param value: value
 */
void Config::App::setValue(const QString &key, const QJsonValue &value)
{
    oApp[key] = value;
    save();
}

/*
 * App keys.
 */
const QString Config::App::kFontSize = "fontSize";
const QString Config::App::kLog      = "log";

/*
 * App default values.
 */
const double Config::App::dFontSize  = 10.25;
const bool Config::App::dLog         = true;

/*
 * Sets all non existing keys to their default
 * value.
 */
void Config::Bar::create()
{
    setDefault(kHeight, dHeight);
    setDefault(kIconSize, dIconSize);
    setDefault(kMargin, dMargin);
    setDefault(kSpacing, dSpacing);
    setDefault(kTimeWidth, dTimeWidth);
    setDefault(kTrackWidth, dTrackWidth);
}

/*
 * Setter for bar height.
 *
 * :param height: height
 */
void Config::Bar::setHeight(int height)
{
    setValue(kHeight, height);
}

/*
 * Getter for bar height.
 *
 * :result: height
 */
int Config::Bar::height()
{
    return oBar[kHeight].toInt();
}

/*
 * Setter for bar icon size.
 *
 * :param size: size
 */
void Config::Bar::setIconSize(int size)
{
    setValue(kIconSize, size);
}

/*
 * Getter for bar icon size.
 *
 * :return: size
 */
int Config::Bar::iconSize()
{
    return oBar[kIconSize].toInt();
}

/*
 * Setter for bar margin.
 *
 * :param margin: margin
 */
void Config::Bar::setMargin(int margin)
{
    setValue(kMargin, margin);
}

/*
 * Getter for bar margin.
 *
 * :return: margin
 */
int Config::Bar::margin()
{
    return oBar[kMargin].toInt();
}

/*
 * Setter for bar spacing.
 *
 * :param spacing: spacing
 */
void Config::Bar::setSpacing(int spacing)
{
    setValue(kSpacing, spacing);
}

/*
 * Getter for bar spacing.
 *
 * :return: spacing
 */
int Config::Bar::spacing()
{
    return oBar[kSpacing].toInt();
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
    setValue(kTimeWidth, width);
}

/*
 * Getter for bar time width.
 *
 * :return: width
 */
int Config::Bar::timeWidth()
{
    return oBar[kTimeWidth].toInt();
}

/*
 * Setter for bar track width.
 *
 * :param width: width
 */
void Config::Bar::setTrackWidth(int width)
{
    setValue(kTimeWidth, width);
}

/*
 * Getter for bar track width.
 *
 * :return: width
 */
int Config::Bar::trackWidth()
{
    return oBar[kTrackWidth].toInt();
}

/*
 * Sets non existing key to its default.
 *
 * :param key: key
 * :param value: value
 */
void Config::Bar::setDefault(const QString &key, const QJsonValue &value)
{
    if (!oBar.contains(key))
        setValue(key, value);
}

/*
 * Sets value at key.
 *
 * :param key: key
 * :param value: value
 */
void Config::Bar::setValue(const QString &key, const QJsonValue &value)
{
    oBar[key] = value;
    save();
}

/*
 * Bar keys.
 */
const QString Config::Bar::kHeight     = "height";
const QString Config::Bar::kIconSize   = "iconSize";
const QString Config::Bar::kMargin     = "margin";
const QString Config::Bar::kSpacing    = "spacing";
const QString Config::Bar::kTimeWidth  = "timeWidth";
const QString Config::Bar::kTrackWidth = "trackWidth";

/*
 * Bar default values.
 */
const int Config::Bar::dHeight         = 68;
const int Config::Bar::dIconSize       = 33;
const int Config::Bar::dMargin         = 8;
const int Config::Bar::dSpacing        = 8;
const int Config::Bar::dTimeWidth      = 50;
const int Config::Bar::dTrackWidth     = 240;

/*
 * Sets all non existing keys to their default
 * value.
 */
void Config::Library::create()
{
    setDefault(kPaths, dPaths);
    setDefault(kItemHeight, dItemHeight);
}

/*
 * Setter for library item height.
 *
 * :param height: height
 */
void Config::Library::setItemHeight(int height)
{
    setValue(kItemHeight, height);
}

/*
 * Getter for library item height.
 *
 * :return: height
 */
int Config::Library::itemHeight()
{
    return oLibrary[kItemHeight].toInt();
}

/*
 * Setter for library paths.
 *
 * :param string: paths
 */
void Config::Library::setPaths(const QStringList &paths)
{
    QJsonArray array;
    for (const QString &path : paths)
        array << QJsonValue::fromVariant(path);

    setValue(kPaths, array);
}

/*
 * Getter for library paths.
 *
 * :return: path
 */
QStringList Config::Library::paths()
{
    QStringList list;
    for (const QJsonValue &element : oLibrary[kPaths].toArray())
        list << element.toString();

    return list;
}

/*
 * Sets non existing key to its default.
 *
 * :param key: key
 * :param value: value
 */
void Config::Library::setDefault(const QString &key, const QJsonValue &value)
{
    if (!oLibrary.contains(key))
        setValue(key, value);
}

/*
 * Overloaded function.
 *
 * :param key: key
 * :param value: value
 */
void Config::Library::setDefault(const QString &key, const QJsonArray &value)
{
    if (!oLibrary.contains(key))
        setValue(key, value);
}

/*
 * Sets value at key.
 *
 * :param key: key
 * :param value: value
 */
void Config::Library::setValue(const QString &key, const QJsonValue &value)
{
    oLibrary[key] = value;
    save();
}

/*
 * Overloaded function.
 *
 * :param key: key
 * :param value: value
 */
void Config::Library::setValue(const QString &key, const QJsonArray &value)
{
    oLibrary[key] = value;
    save();
}

/*
 * Library keys.
 */
const QString Config::Library::kItemHeight = "itemHeight";
const QString Config::Library::kPaths      = "paths";

/*
 * Library default values.
 */
const int Config::Library::dItemHeight     = 50;
const QJsonArray Config::Library::dPaths   = {QStandardPaths::writableLocation(QStandardPaths::MusicLocation)};

/*
 * Sets all non existing keys to their default
 * value.
 */
void Config::Player::create()
{
    setDefault(kVolume, dVolume);
    setDefault(kShuffle, dShuffle);
    setDefault(kLoop, dLoop);
}

/*
 * Setter for player loop.
 *
 * :param loop: loop
 */
void Config::Player::setLoop(bool loop)
{
    setValue(kLoop, loop);
}

/*
 * Getter for player loop.
 *
 * :return: loop
 */
bool Config::Player::loop()
{
    return oPlayer[kLoop].toBool();
}

/*
 * Setter for player shuffle.
 *
 * :param shuffle: shuffle
 */
void Config::Player::setShuffle(bool shuffle)
{
    setValue(kShuffle, shuffle);
}

/*
 * Getter for player shuffle.
 *
 * :return: shuffle
 */
bool Config::Player::shuffle()
{
    return oPlayer[kShuffle].toBool();
}

/*
 * Setter for player volume.
 *
 * :param volume: volume
 */
void Config::Player::setVolume(int volume)
{
    setValue(kVolume, volume);
}

/*
 * Getter for player volume.
 *
 * :return: volume
 */
int Config::Player::volume()
{
    return oPlayer[kVolume].toInt();
}

/*
 * Sets non existing key to its default.
 *
 * :param key: key
 * :param value: value
 */
void Config::Player::setDefault(const QString &key, const QJsonValue &value)
{
    if (!oPlayer.contains(key))
        setValue(key, value);
}

/*
 * Sets value at key.
 *
 * :param key: key
 * :param value: value
 */
void Config::Player::setValue(const QString &key, const QJsonValue &value)
{
    oPlayer[key] = value;
    save();
}

/*
 * Player keys.
 */
const QString Config::Player::kLoop    = "loop";
const QString Config::Player::kShuffle = "shuffle";
const QString Config::Player::kVolume  = "volume";

/*
 * Player default values.
 */
const bool Config::Player::dLoop       = false;
const bool Config::Player::dShuffle    = false;
const int Config::Player::dVolume      = 25;

/*
 * Sets all non existing keys to their default
 * value.
 */
void Config::Shortcut::create()
{
    setDefault(kNext, dNext);
    setDefault(kPlayPause, dPlayPause);
    setDefault(kPrevious, dPrevious);
    setDefault(kVolumeDown, dVolumeDown);
    setDefault(kVolumeUp, dVolumeUp);
}

/*
 * Setter for next shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setNext(const QString &shortcut)
{
    setValue(kNext, shortcut);
}

/*
 * Getter for next shortcut.
 *
 * :return: shortcut
 */
QString Config::Shortcut::next()
{
    return oShortcut[kNext].toString();
}

/*
 * Setter for play pause shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setPlayPause(const QString &shortcut)
{
    setValue(kPlayPause, shortcut);
}

/*
 * Getter for play pause shortcut.
 *
 * :return: shortcut
 */
QString Config::Shortcut::playPause()
{
    return oShortcut[kPlayPause].toString();
}

/*
 * Setter for previous shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setPrevious(const QString &shortcut)
{
    setValue(kPrevious, shortcut);
}

/*
 * Getter for previous shortcut.
 *
 * :return: shortcut
 */
QString Config::Shortcut::previous()
{
    return oShortcut[kPrevious].toString();
}

/*
 * Setter for volume down shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setVolumeDown(const QString &shortcut)
{
    setValue(kVolumeDown, shortcut);
}

/*
 * Getter for volume down shortcut.
 *
 * :return: shortcut
 */
QString Config::Shortcut::volumeDown()
{
    return oShortcut[kVolumeDown].toString();
}

/*
 * Setter for volume up shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setVolumeUp(const QString &shortcut)
{
    setValue(kVolumeUp, shortcut);
}

/*
 * Getter for volume up shortcut.
 *
 * :return: shortcut
 */
QString Config::Shortcut::volumeUp()
{
    return oShortcut[kVolumeUp].toString();
}

/*
 * Sets non existing key to its default.
 *
 * :param key: key
 * :param value: value
 */
void Config::Shortcut::setDefault(const QString &key, const QJsonValue &value)
{
    if (!oShortcut.contains(key))
        setValue(key, value);
}

/*
 * Sets value at key.
 *
 * :param key: key
 * :param value: value
 */
void Config::Shortcut::setValue(const QString &key, const QJsonValue &value)
{
    oShortcut[key] = value;
    save();
}

/*
 * Shortcut keys.
 */
const QString Config::Shortcut::kNext       = "next";
const QString Config::Shortcut::kPlayPause  = "playPause";
const QString Config::Shortcut::kPrevious   = "previous";
const QString Config::Shortcut::kVolumeDown = "volumeDown";
const QString Config::Shortcut::kVolumeUp   = "volumeUp";

/*
 * Shortcut default values.
 */
const QString Config::Shortcut::dNext       = "Ctrl+F12";
const QString Config::Shortcut::dPlayPause  = "Ctrl+F11";
const QString Config::Shortcut::dPrevious   = "Ctrl+F10";
const QString Config::Shortcut::dVolumeDown = "Ctrl+F7";
const QString Config::Shortcut::dVolumeUp   = "Ctrl+F8";


/*
 * Saves the made changes by writing it to the file.
 */
void Config::save()
{
    saveObjects();

    QFile file(CFG_PATH);
    if (file.open(QFile::WriteOnly))
        file.write(jDocument.toJson());
}

/*
 * Reads or creates the config file.
 */
void Config::load()
{
    jDocument = QJsonDocument::fromJson("{}");
    if (Utils::exists(CFG_PATH))
    {
        QFile file(CFG_PATH);
        if (file.open(QIODevice::ReadOnly))
            jDocument = QJsonDocument::fromJson(file.readAll());
    }
    loadObjects();
}

/*
 * Saves objects.
 */
void Config::saveObjects()
{
    QJsonObject object = jDocument.object();
    object[kApp] = oApp;
    object[kShortcut] = oShortcut;
    object[kPlayer] = oPlayer;
    object[kLibrary] = oLibrary;
    object[kBar] = oBar;
    jDocument.setObject(object);
}

/*
 * Loads objects.
 */
void Config::loadObjects()
{
    QJsonObject object = jDocument.object();
    oApp = object[kApp].toObject();
    oShortcut = object[kShortcut].toObject();
    oPlayer = object[kPlayer].toObject();
    oLibrary = object[kLibrary].toObject();
    oBar = object[kBar].toObject();
}

/*
 * Json document.
 */
QJsonDocument Config::jDocument;

/*
 * Main json objects.
 */
QJsonObject Config::oApp;
QJsonObject Config::oBar;
QJsonObject Config::oLibrary;
QJsonObject Config::oPlayer;
QJsonObject Config::oShortcut;

/*
 * Main json object keys.
 */
const QString Config::kApp      = "app";
const QString Config::kBar      = "bar";
const QString Config::kLibrary  = "library";
const QString Config::kPlayer   = "player";
const QString Config::kShortcut = "shortcut";
