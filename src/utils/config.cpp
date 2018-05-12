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
    setDefault(oApp, kFontSize, dFontSize);
    setDefault(oApp, kLog, dLog);
}

/*
 * Setter for app font size.
 *
 * :param size: size
 */
void Config::App::setFontSize(double size)
{
    setValue(oApp, kFontSize, size);
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
    setValue(oApp, kLog, log);
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
    setDefault(oBar, kGrooveHeight, dGrooveHeight);
    setDefault(oBar, kHandleSize, dHandleSize);
    setDefault(oBar, kHeight, dHeight);
    setDefault(oBar, kIconSize, dIconSize);
    setDefault(oBar, kMargin, dMargin);
    setDefault(oBar, kSpacing, dSpacing);
    setDefault(oBar, kTimeWidth, dTimeWidth);
    setDefault(oBar, kTrackWidth, dTrackWidth);
}

/*
 * Setter for groove height.
 *
 * :param height: height
 */
void Config::Bar::setGrooveHeight(int height)
{
    setValue(oBar, kGrooveHeight, height);
}

/*
 * Getter for groove height.
 *
 * :return: height
 */
int Config::Bar::grooveHeight()
{
    return makeEven(scale(oBar[kGrooveHeight].toInt()));
}

/*
 * Setter for handle size.
 *
 * :param size: size
 */
void Config::Bar::setHandleSize(int size)
{
    setValue(oBar, kHandleSize, size);
}

/*
 * Getter for groove height.
 *
 * :return height
 */
int Config::Bar::handleSize()
{
    return  makeEven(scale(oBar[kHandleSize].toInt()));
}

/*
 * Setter for bar height.
 *
 * :param height: height
 */
void Config::Bar::setHeight(int height)
{
    setValue(oBar, kHeight, height);
}

/*
 * Getter for bar height.
 *
 * :result: height
 */
int Config::Bar::height()
{
    return makeEven(scale(oBar[kHeight].toInt()));
}

/*
 * Setter for bar icon size.
 *
 * :param size: size
 */
void Config::Bar::setIconSize(int size)
{
    setValue(oBar, kIconSize, size);
}

/*
 * Getter for bar icon size.
 *
 * :return: size
 */
int Config::Bar::iconSize()
{
    return makeEven(scale(oBar[kIconSize].toInt()));
}

/*
 * Setter for bar margin.
 *
 * :param margin: margin
 */
void Config::Bar::setMargin(int margin)
{
    setValue(oBar, kMargin, margin);
}

/*
 * Getter for bar margin.
 *
 * :return: margin
 */
int Config::Bar::margin()
{
    return scale(oBar[kMargin].toInt());
}

/*
 * Setter for bar spacing.
 *
 * :param spacing: spacing
 */
void Config::Bar::setSpacing(int spacing)
{
    setValue(oBar, kSpacing, spacing);
}

/*
 * Getter for bar spacing.
 *
 * :return: spacing
 */
int Config::Bar::spacing()
{
    return scale(oBar[kSpacing].toInt());
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
    setValue(oBar, kTimeWidth, width);
}

/*
 * Getter for bar time width.
 *
 * :return: width
 */
int Config::Bar::timeWidth()
{
    return scale(oBar[kTimeWidth].toInt());
}

/*
 * Setter for bar track width.
 *
 * :param width: width
 */
void Config::Bar::setTrackWidth(int width)
{
    setValue(oBar, kTimeWidth, width);
}

/*
 * Getter for bar track width.
 *
 * :return: width
 */
int Config::Bar::trackWidth()
{
    return scale(oBar[kTrackWidth].toInt());
}

/*
 * Bar keys.
 */
const QString Config::Bar::kGrooveHeight = "grooveHeight";
const QString Config::Bar::kHandleSize   = "handleSize";
const QString Config::Bar::kHeight       = "height";
const QString Config::Bar::kIconSize     = "iconSize";
const QString Config::Bar::kMargin       = "margin";
const QString Config::Bar::kSpacing      = "spacing";
const QString Config::Bar::kTimeWidth    = "timeWidth";
const QString Config::Bar::kTrackWidth   = "trackWidth";

/*
 * Bar default values.
 */
const int Config::Bar::dGrooveHeight     = 2;
const int Config::Bar::dHandleSize       = 16;
const int Config::Bar::dHeight           = 68;
const int Config::Bar::dIconSize         = 32;
const int Config::Bar::dMargin           = 8;
const int Config::Bar::dSpacing          = 8;
const int Config::Bar::dTimeWidth        = 50;
const int Config::Bar::dTrackWidth       = 240;

/*
 * Sets all non existing keys to their default
 * value.
 */
void Config::Library::create()
{
    setDefault(oLibrary, kPaths, dPaths);
    setDefault(oLibrary, kItemHeight, dItemHeight);
    setDefault(oLibrary, kScrollBarWidth, dScrollBarWidth);
}

/*
 * Setter for library item height.
 *
 * :param height: height
 */
void Config::Library::setItemHeight(int height)
{
    setValue(oLibrary, kItemHeight, height);
}

/*
 * Getter for library item height.
 *
 * :return: height
 */
int Config::Library::itemHeight()
{
    return scale(oLibrary[kItemHeight].toInt());
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

    setValue(oLibrary, kPaths, array);
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
 * Setter for scroll bar width.
 *
 * :param width: width
 */
void Config::Library::setScrollBarWidth(int width)
{
    setValue(oLibrary, kScrollBarWidth, width);
}

/*
 * Getter for scroll bar width.
 *
 * :return: width
 */
int Config::Library::scrollBarWidth()
{
    return scale(oLibrary[kScrollBarWidth].toInt());
}

/*
 * Library keys.
 */
const QString Config::Library::kItemHeight     = "itemHeight";
const QString Config::Library::kPaths          = "paths";
const QString Config::Library::kScrollBarWidth = "scrollBarWidth";

/*
 * Library default values.
 */
const int Config::Library::dItemHeight         = 50;
const QJsonArray Config::Library::dPaths       = {QStandardPaths::writableLocation(QStandardPaths::MusicLocation)};
const int Config::Library::dScrollBarWidth     = 10;

/*
 * Sets all non existing keys to their default
 * value.
 */
void Config::Player::create()
{
    setDefault(oPlayer, kVolume, dVolume);
    setDefault(oPlayer, kShuffle, dShuffle);
    setDefault(oPlayer, kLoop, dLoop);
}

/*
 * Setter for player loop.
 *
 * :param loop: loop
 */
void Config::Player::setLoop(bool loop)
{
    setValue(oPlayer, kLoop, loop);
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
    setValue(oPlayer, kShuffle, shuffle);
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
    setValue(oPlayer, kVolume, volume);
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
    setDefault(oShortcut, kNext, dNext);
    setDefault(oShortcut, kPlayPause, dPlayPause);
    setDefault(oShortcut, kPrevious, dPrevious);
    setDefault(oShortcut, kVolumeDown, dVolumeDown);
    setDefault(oShortcut, kVolumeUp, dVolumeUp);
}

/*
 * Setter for next shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setNext(const QString &shortcut)
{
    setValue(oShortcut, kNext, shortcut);
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
    setValue(oShortcut, kPlayPause, shortcut);
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
    setValue(oShortcut, kPrevious, shortcut);
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
    setValue(oShortcut, kVolumeDown, shortcut);
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
    setValue(oShortcut, kVolumeUp, shortcut);
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
    object[kBar] = oBar;
    object[kLibrary] = oLibrary;
    object[kPlayer] = oPlayer;
    object[kShortcut] = oShortcut;
    jDocument.setObject(object);
}

/*
 * Loads objects.
 */
void Config::loadObjects()
{
    QJsonObject object = jDocument.object();
    oApp = object[kApp].toObject();
    oBar = object[kBar].toObject();
    oLibrary = object[kLibrary].toObject();
    oPlayer = object[kPlayer].toObject();
    oShortcut = object[kShortcut].toObject();
}

/*
 * Sets value at key and saves changes.
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
 * Sets value at key and saves changes.
 *
 * :param object: object
 * :param key: key
 * :param value: value
 */
void Config::setValue(QJsonObject &object, const QString &key, const QJsonArray &value)
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
 * Sets value if the key does not exist.
 *
 * :param object: object
 * :param key: key
 * :param value: value
 */
void Config::setDefault(QJsonObject &object, const QString &key, const QJsonArray &value)
{
    if (!object.contains(key))
        setValue(object, key, value);
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
 * Makes a value even to prevent user
 * interface alignment problems.
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
