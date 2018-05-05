#include "config.hpp"

/*
 * Creates settings and sets all non existing
 * keys to their default value.
 */
void Config::create()
{
    if (config)
        return;

    config = new QSettings(CFG_PATH, QSettings::IniFormat, qApp);

    App::create();
    Shortcut::create();
    Player::create();
    Library::create();
    Bar::create();
}

/*
 * Sets all non existing keys to their default
 * value.
 */
void Config::App::create()
{
    if (!App::contains(kLog))
        App::setLog(dLog);

    if (!App::contains(kFontSize))
        App::setFontSize(dFontSize);
}

/*
 * Checks if app contains key.
 *
 * :param key: key
 * :return: contains
 */
bool Config::App::contains(const QString &key)
{
    return Config::contains(kApp, key);
}

/*
 * Setter for app log.
 *
 * :param log: log
 */
void Config::App::setLog(bool log)
{
    Config::setValue(kApp, kLog, log);
}

/*
 * Getter for app log.
 *
 * :return: log
 */
bool Config::App::log()
{
    return Config::value(kApp, kLog, dLog).toBool();
}

/*
 * Setter for app font size.
 *
 * :param size: size
 */
void Config::App::setFontSize(double size)
{
    Config::setValue(kApp, kFontSize, size);
}

/*
 * Getter for app font size.
 *
 * :return: size
 */
double Config::App::fontSize()
{
    return Config::value(kApp, kFontSize, dFontSize).toDouble();
}

/*
 * App group.
 */
const QString Config::App::kApp      = "App";

/*
 * App section keys.
 */
const QString Config::App::kLog      = "Log";
const QString Config::App::kFontSize = "FontSize";

/*
 * App section default values.
 */
const bool Config::App::dLog         = true;
const double Config::App::dFontSize  = 10.25;

/*
 * Sets all non existing keys to their default
 * value.
 */
void Config::Shortcut::create()
{
    if (!Shortcut::contains(kPlayPause))
        Shortcut::setPlayPause(dPlayPause);

    if (!Shortcut::contains(kNext))
        Shortcut::setNext(dNext);

    if (!Shortcut::contains(kPrevious))
        Shortcut::setPrevious(dPrevious);

    if (!Shortcut::contains(kVolumeUp))
        Shortcut::setVolumeUp(dVolumeUp);

    if (!Shortcut::contains(kVolumeDown))
        Shortcut::setVolumeDown(dVolumeDown);
}

/*
 * Checks if shortcut contains key.
 *
 * :param key: key
 * :return: contains
 */
bool Config::Shortcut::contains(const QString &key)
{
    return Config::contains(kShortcut, key);
}


/*
 * Setter for play pause shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setPlayPause(const QString &shortcut)
{
    Config::setValue(kShortcut, kPlayPause, shortcut);
}

/*
 * Getter for play pause shortcut.
 *
 * :return: shortcut
 */
QString Config::Shortcut::playPause()
{
    return Config::value(kShortcut, kPlayPause, dPlayPause).toString();
}

/*
 * Setter for next shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setNext(const QString &shortcut)
{
    Config::setValue(kShortcut, kNext, shortcut);
}

/*
 * Getter for next shortcut.
 *
 * :return: shortcut
 */
QString Config::Shortcut::next()
{
    return Config::value(kShortcut, kNext, dNext).toString();
}

/*
 * Setter for previous shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setPrevious(const QString &shortcut)
{
    Config::setValue(kShortcut, kPrevious, shortcut);
}

/*
 * Getter for previous shortcut.
 *
 * :return: shortcut
 */
QString Config::Shortcut::previous()
{
    return Config::value(kShortcut, kPrevious, dPrevious).toString();
}

/*
 * Setter for volume up shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setVolumeUp(const QString &shortcut)
{
    Config::setValue(kShortcut, kVolumeUp, shortcut);
}

/*
 * Getter for volume up shortcut.
 *
 * :return: shortcut
 */
QString Config::Shortcut::volumeUp()
{
    return Config::value(kShortcut, kVolumeUp, dVolumeUp).toString();
}

/*
 * Setter for volume down shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::Shortcut::setVolumeDown(const QString &shortcut)
{
    Config::setValue(kShortcut, kVolumeDown, shortcut);
}

/*
 * Getter for volume down shortcut.
 *
 * :return: shortcut
 */
QString Config::Shortcut::volumeDown()
{
    return Config::value(kShortcut, kVolumeDown, dVolumeDown).toString();
}

/*
 * Shortcut section.
 */
const QString Config::Shortcut::kShortcut   = "Shortcut";

/*
 * Shortcut keys.
 */
const QString Config::Shortcut::kPlayPause  = "PlayPause";
const QString Config::Shortcut::kNext       = "Next";
const QString Config::Shortcut::kPrevious   = "Previous";
const QString Config::Shortcut::kVolumeUp   = "VolumeUp";
const QString Config::Shortcut::kVolumeDown = "VolumeDown";

/*
 * Shortcut default values.
 */
const QString Config::Shortcut::dPlayPause  = "Ctrl+F11";
const QString Config::Shortcut::dNext       = "Ctrl+F12";
const QString Config::Shortcut::dPrevious   = "Ctrl+F10";
const QString Config::Shortcut::dVolumeUp   = "Ctrl+F8";
const QString Config::Shortcut::dVolumeDown = "Ctrl+F7";

/*
 * Sets all non existing keys to their default
 * value.
 */
void Config::Player::create()
{
    if (!Player::contains(kVolume))
        Player::setVolume(dVolume);

    if (!Player::contains(kShuffle))
        Player::setShuffle(dShuffle);

    if (!Player::contains(kLoop))
        Player::setLoop(dLoop);
}

/*
 * Checks if player contains key.
 *
 * :param key: key
 * :return: contains
 */
bool Config::Player::contains(const QString &key)
{
    return Config::contains(kPlayer, key);
}

/*
 * Setter for player volume.
 *
 * :param volume: volume
 */
void Config::Player::setVolume(int volume)
{
    Config::setValue(kPlayer, kVolume, volume);
}

/*
 * Getter for player volume.
 *
 * :return: volume
 */
int Config::Player::volume()
{
    return Config::value(kPlayer, kVolume, dVolume).toInt();
}

/*
 * Setter for player shuffle.
 *
 * :param shuffle: shuffle
 */
void Config::Player::setShuffle(bool shuffle)
{
    Config::setValue(kPlayer, kShuffle, shuffle);
}

/*
 * Getter for player shuffle.
 *
 * :return: shuffle
 */
bool Config::Player::shuffle()
{
    return Config::value(kPlayer, kShuffle, dShuffle).toBool();
}

/*
 * Setter for player loop.
 *
 * :param loop: loop
 */
void Config::Player::setLoop(bool loop)
{
    Config::setValue(kPlayer, kLoop, loop);
}

/*
 * Getter for player loop.
 *
 * :return: loop
 */
bool Config::Player::loop()
{
    return Config::value(kPlayer, kLoop, dLoop).toBool();
}

/*
 * Player section.
 */
const QString Config::Player::kPlayer  = "Player";

/*
 * Player keys.
 */
const QString Config::Player::kVolume  = "Volume";
const QString Config::Player::kShuffle = "Shuffle";
const QString Config::Player::kLoop    = "Loop";

/*
 * Player default values.
 */
const int Config::Player::dVolume      = 25;
const bool Config::Player::dShuffle    = false;
const bool Config::Player::dLoop       = false;

/*
 * Sets all non existing keys to their default
 * value.
 */
void Config::Library::create()
{
    if (!Library::contains(kPath))
        Library::setPath(dPath);

    if (!Library::contains(kItemHeight))
        Library::setItemHeight(dItemHeight);
}

/*
 * Checks if library contains key.
 *
 * :param key: key
 * :return: contains
 */
bool Config::Library::contains(const QString &key)
{
    return Config::contains(kLibrary, key);
}

/*
 * Setter for library path.
 *
 * :param string: path
 */
void Config::Library::setPath(const QString &path)
{
    Config::setValue(kLibrary, kPath, path);
}

/*
 * Getter for library path.
 *
 * :return: path
 */
QString Config::Library::path()
{
    return Config::value(kLibrary, kPath, dPath).toString();
}

/*
 * Setter for library item height.
 *
 * :param height: height
 */
void Config::Library::setItemHeight(int height)
{
    Config::setValue(kLibrary, kItemHeight, height);
}

/*
 * Getter for library item height.
 *
 * :return: height
 */
int Config::Library::itemHeight()
{
    return Config::value(kLibrary, kItemHeight, dItemHeight).toInt();
}

/*
 * Library section.
 */
const QString Config::Library::kLibrary    = "Library";

/*
 * Library keys.
 */
const QString Config::Library::kPath       = "Path";
const QString Config::Library::kItemHeight = "ItemHeight";

/*
 * Library default values.
 */
const QString Config::Library::dPath       = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
const int Config::Library::dItemHeight     = 50;

/*
 * Sets all non existing keys to their default
 * value.
 */
void Config::Bar::create()
{
    if (!Bar::contains(kHeight))
        Bar::setHeight(dHeight);

    if (!Bar::contains(kMargin))
        Bar::setMargin(dMargin);

    if (!Bar::contains(kSpacing))
        Bar::setSpacing(dSpacing);

    if (!Bar::contains(kIconSize))
        Bar::setIconSize(dIconSize);

    if (!Bar::contains(kTrackWidth))
        Bar::setTrackWidth(dTrackWidth);

    if (!Bar::contains(kTimeWidth))
        Bar::setTimeWidth(dTimeWidth);
}

/*
 * Checks if bar contains key.
 *
 * :param key: key
 * :return: contains
 */
bool Config::Bar::contains(const QString &key)
{
    return Config::contains(kBar, key);
}

/*
 * Setter for bar height.
 *
 * :param height: height
 */
void Config::Bar::setHeight(int height)
{
    Config::setValue(kBar, kHeight, height);
}

/*
 * Getter for bar height.
 *
 * :result: height
 */
int Config::Bar::height()
{
    return Config::value(kBar, kHeight, dHeight).toInt();
}

/*
 * Setter for bar margin.
 *
 * :param margin: margin
 */
void Config::Bar::setMargin(int margin)
{
    Config::setValue(kBar, kMargin, margin);
}

/*
 * Getter for bar margin.
 *
 * :return: margin
 */
int Config::Bar::margin()
{
    return Config::value(kBar, kMargin, dMargin).toInt();
}

/*
 * Setter for bar spacing.
 *
 * :param spacing: spacing
 */
void Config::Bar::setSpacing(int spacing)
{
    Config::setValue(kBar, kSpacing, spacing);
}

/*
 * Getter for bar spacing.
 *
 * :return: spacing
 */
int Config::Bar::spacing()
{
    return Config::value(kBar, kSpacing, dSpacing).toInt();
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
 * Setter for bar icon size.
 *
 * :param size: size
 */
void Config::Bar::setIconSize(int size)
{
    Config::setValue(kBar, kIconSize, size);
}

/*
 * Getter for bar icon size.
 *
 * :return: size
 */
int Config::Bar::iconSize()
{
    return Config::value(kBar, kIconSize, dIconSize).toInt();
}

/*
 * Setter for bar track width.
 *
 * :param width: width
 */
void Config::Bar::setTrackWidth(int width)
{
    Config::setValue(kBar, kTrackWidth, width);
}

/*
 * Getter for bar track width.
 *
 * :return: width
 */
int Config::Bar::trackWidth()
{
    return Config::value(kBar, kTrackWidth, dTrackWidth).toInt();
}

/*
 * Setter for bar time width.
 *
 * :param width: width
 */
void Config::Bar::setTimeWidth(int width)
{
    Config::setValue(kBar, kTimeWidth, width);
}

/*
 * Getter for bar time width.
 *
 * :return: width
 */
int Config::Bar::timeWidth()
{
    return Config::value(kBar, kTimeWidth, dTimeWidth).toInt();
}

/*
 * Bar group.
 */
const QString Config::Bar::kBar        = "Bar";

/*
 * Bar keys.
 */
const QString Config::Bar::kHeight     = "Height";
const QString Config::Bar::kSpacing    = "Spacing";
const QString Config::Bar::kMargin     = "Margin";
const QString Config::Bar::kIconSize   = "IconSize";
const QString Config::Bar::kTrackWidth = "TrackWidth";
const QString Config::Bar::kTimeWidth  = "TimeWidth";

/*
 * Bar default values.
 */
const int Config::Bar::dHeight         = 68;
const int Config::Bar::dSpacing        = 8;
const int Config::Bar::dMargin         = 8;
const int Config::Bar::dIconSize       = 33;
const int Config::Bar::dTrackWidth     = 240;
const int Config::Bar::dTimeWidth      = 50;

/*
 * Checks if group contains key.
 *
 * :param group: group
 * :param key: key
 * :return: exists
 */
bool Config::contains(const QString &group, const QString &key)
{
    config->beginGroup(group);
    bool contains = config->contains(key);
    config->endGroup();

    return contains;
}

/*
 * Sets a config value.
 *
 * :param group: group
 * :param key: key
 * :param value: value
 */
void Config::setValue(const QString &group, const QString &key, const QVariant &value)
{
    config->beginGroup(group);
    config->setValue(key, value);
    config->endGroup();
}

/*
 * Gets a config value.
 *
 * :param group: group
 * :param key: key
 * :param defaultValue: default value
 * :return: value
 */
QVariant Config::value(const QString &group, const QString &key, const QVariant &defaultValue)
{
    config->beginGroup(group);
    QVariant value = config->value(key, defaultValue);
    config->endGroup();

    return value;
}

/*
 * Config pointer.
 */
QSettings * Config::config = nullptr;
