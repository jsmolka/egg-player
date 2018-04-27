#include "config.hpp"

/*
 * Creates settings and sets all non existing
 * keys to their default value.
 */
void Config::create()
{
    if (config)
        return;

    config = new QSettings(CFG_PATH, QSettings::IniFormat, QApplication::instance());

    if (!sectionContains(kApp, kALog))
        ALog(dALog);

    if (!sectionContains(kApp, kAFontSize))
        AFontSize(dAFontSize);

    if (!sectionContains(kShortcut, kSPlayPause))
        SPlayPause(dSPlayPause);

    if (!sectionContains(kShortcut, kSNext))
        SNext(dSNext);

    if (!sectionContains(kShortcut, kSPrevious))
        SPrevious(dSPrevious);

    if (!sectionContains(kShortcut, kSVolumeUp))
        SVolumeUp(dSVolumeUp);

    if (!sectionContains(kShortcut, kSVolumeDown))
        SVolumeDown(dSVolumeDown);

    if (!sectionContains(kPlayer, kPVolume))
        PVolume(dPVolume);

    if (!sectionContains(kPlayer, kPShuffle))
        PShuffle(dPShuffle);

    if (!sectionContains(kPlayer, kPLoop))
        PLoop(dPLoop);

    if (!sectionContains(kLibrary, kLPath))
        LPath(dLPath);

    if (!sectionContains(kLibrary, kLItemHeight))
        LItemHeight(dLItemHeight);

    if (!sectionContains(kBar, kBHeight))
        BHeight(dBHeight);

    if (!sectionContains(kBar, kBSpacing))
        BSpacing(dBSpacing);

    if (!sectionContains(kBar, kBCoverSize))
        BCoverSize(dBCoverSize);

    if (!sectionContains(kBar, kBIconSize))
        BIconSize(dBIconSize);

    if (!sectionContains(kBar, kBTrackWidth))
        BTrackWidth(dBTrackWidth);

    if (!sectionContains(kBar, kBTimeWidth))
        BTimeWidth(dBTimeWidth);
}

/*
 * Setter for app log.
 *
 * :param log: log
 */
void Config::ALog(bool log)
{
    config->beginGroup(kApp);
    config->setValue(kALog, log);
    config->endGroup();
}

/*
 * Getter for app log.
 *
 * :return: log
 */
bool Config::ALog()
{
    config->beginGroup(kApp);
    bool log = config->value(kALog, dALog).toBool();
    config->endGroup();

    return log;
}

/*
 * Setter for app font size.
 *
 * :param size: size
 */
void Config::AFontSize(double size)
{
    config->beginGroup(kApp);
    config->setValue(kAFontSize, size);
    config->endGroup();
}

/*
 * Getter for app font size.
 *
 * :return: size
 */
double Config::AFontSize()
{
    config->beginGroup(kApp);
    double size = config->value(kAFontSize, dAFontSize).toDouble();
    config->endGroup();

    return size;
}

/*
 * Setter for play pause shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::SPlayPause(const QString &shortcut)
{
    config->beginGroup(kShortcut);
    config->setValue(kSPlayPause, shortcut);
    config->endGroup();
}

/*
 * Getter for play pause shortcut
 *
 * :return: shortcut
 */
QString Config::SPlayPause()
{
    config->beginGroup(kShortcut);
    QString shortcut = config->value(kSPlayPause, dSPlayPause).toString();
    config->endGroup();

    return shortcut;
}

/*
 * Setter for next shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::SNext(const QString &shortcut)
{
    config->beginGroup(kShortcut);
    config->setValue(kSNext, shortcut);
    config->endGroup();
}

/*
 * Getter for next shortcut
 *
 * :return: shortcut
 */
QString Config::SNext()
{
    config->beginGroup(kShortcut);
    QString shortcut = config->value(kSNext, dSNext).toString();
    config->endGroup();

    return shortcut;
}

/*
 * Setter for previous shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::SPrevious(const QString &shortcut)
{
    config->beginGroup(kShortcut);
    config->setValue(kSPrevious, shortcut);
    config->endGroup();
}

/*
 * Getter for previous shortcut
 *
 * :return: shortcut
 */
QString Config::SPrevious()
{
    config->beginGroup(kShortcut);
    QString shortcut = config->value(kSPrevious, dSPrevious).toString();
    config->endGroup();

    return shortcut;
}

/*
 * Setter for volume up shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::SVolumeUp(const QString &shortcut)
{
    config->beginGroup(kShortcut);
    config->setValue(kSVolumeUp, shortcut);
    config->endGroup();
}

/*
 * Getter for volume up shortcut
 *
 * :return: shortcut
 */
QString Config::SVolumeUp()
{
    config->beginGroup(kShortcut);
    QString shortcut = config->value(kSVolumeUp, dSVolumeUp).toString();
    config->endGroup();

    return shortcut;
}

/*
 * Setter for volume down shortcut.
 *
 * :param shortcut: shortcut
 */
void Config::SVolumeDown(const QString &shortcut)
{
    config->beginGroup(kShortcut);
    config->setValue(kSVolumeDown, shortcut);
    config->endGroup();
}

/*
 * Getter for volume down shortcut
 *
 * :return: shortcut
 */
QString Config::SVolumeDown()
{
    config->beginGroup(kShortcut);
    QString shortcut = config->value(kSVolumeDown, dSVolumeDown).toString();
    config->endGroup();

    return shortcut;
}

/*
 * Setter for player volume.
 *
 * :param volume: volume
 */
void Config::PVolume(int volume)
{
    config->beginGroup(kPlayer);
    config->setValue(kPVolume, volume);
    config->endGroup();
}

/*
 * Getter for player volume.
 *
 * :return: volume
 */
int Config::PVolume()
{
    config->beginGroup(kPlayer);
    int volume = config->value(kPVolume, dPVolume).toInt();
    config->endGroup();

    return volume;
}

/*
 * Setter for player shuffle.
 *
 * :param shuffle: shuffle
 */
void Config::PShuffle(bool shuffle)
{
    config->beginGroup(kPlayer);
    config->setValue(kPShuffle, shuffle);
    config->endGroup();
}

/*
 * Getter for player shuffle.
 *
 * :return: shuffle
 */
bool Config::PShuffle()
{
    config->beginGroup(kPlayer);
    bool shuffle = config->value(kPShuffle, dPShuffle).toBool();
    config->endGroup();

    return shuffle;
}

/*
 * Setter for player loop.
 *
 * :param loop: loop
 */
void Config::PLoop(bool loop)
{
    config->beginGroup(kPlayer);
    config->setValue(kPLoop, loop);
    config->endGroup();
}

/*
 * Getter for player loop.
 *
 * :return: loop
 */
bool Config::PLoop()
{
    config->beginGroup(kPlayer);
    bool loop = config->value(kPLoop, dPLoop).toBool();
    config->endGroup();

    return loop;
}

/*
 * Setter for library path.
 *
 * :param string: path
 */
void Config::LPath(const QString &path)
{
    config->beginGroup(kLibrary);
    config->setValue(kLPath, path);
    config->endGroup();
}

/*
 * Getter for library path.
 *
 * :return: path
 */
QString Config::LPath()
{
    config->beginGroup(kLibrary);
    QString path = config->value(kLPath, dLPath).toString();
    config->endGroup();

    return path;
}

/*
 * Setter for library item height.
 *
 * :param height: height
 */
void Config::LItemHeight(int height)
{
    config->beginGroup(kLibrary);
    config->setValue(kLItemHeight, height);
    config->endGroup();
}

/*
 * Getter for library item height.
 *
 * :return: height
 */
int Config::LItemHeight()
{
    config->beginGroup(kLibrary);
    int height = config->value(kLItemHeight, dLItemHeight).toInt();
    config->endGroup();

    return height;
}

/*
 * Setter for bar height.
 *
 * :param height: height
 */
void Config::BHeight(int height)
{
    config->beginGroup(kBar);
    config->setValue(kBHeight, height);
    config->endGroup();
}

/*
 * Getter for bar height.
 *
 * :result: height
 */
int Config::BHeight()
{
    config->beginGroup(kBar);
    int height = config->value(kBHeight, dBHeight).toInt();
    config->endGroup();

    return height;
}

/*
 * Setter for bar spacing.
 *
 * :param spacing: spacing
 */
void Config::BSpacing(int spacing)
{
    config->beginGroup(kBar);
    config->setValue(kBSpacing, spacing);
    config->endGroup();
}

/*
 * Getter for bar spacing.
 *
 * :return: spacing
 */
int Config::BSpacing()
{
    config->beginGroup(kBar);
    int spacing = config->value(kBSpacing, dBSpacing).toInt();
    config->endGroup();

    return spacing;
}

/*
 * Setter for bar cover size.
 *
 * :param size: size
 */
void Config::BCoverSize(int size)
{
    config->beginGroup(kBar);
    config->setValue(kBCoverSize, size);
    config->endGroup();
}

/*
 * Getter for bar cover size.
 *
 * :return: size
 */
int Config::BCoverSize()
{
    config->beginGroup(kBar);
    int size = config->value(kBCoverSize, dBCoverSize).toInt();
    config->endGroup();

    return size;
}

/*
 * Setter for bar icon size.
 *
 * :param size: size
 */
void Config::BIconSize(int size)
{
    config->beginGroup(kBar);
    config->setValue(kBIconSize, size);
    config->endGroup();
}

/*
 * Getter for bar icon size.
 *
 * :return: size
 */
int Config::BIconSize()
{
    config->beginGroup(kBar);
    int size = config->value(kBIconSize, dBIconSize).toInt();
    config->endGroup();

    return size;
}

/*
 * Setter for bar track width.
 *
 * :param width: width
 */
void Config::BTrackWidth(int width)
{
    config->beginGroup(kBar);
    config->setValue(kBTrackWidth, width);
    config->endGroup();
}

/*
 * Getter for bar track width.
 *
 * :return: width
 */
int Config::BTrackWidth()
{
    config->beginGroup(kBar);
    int width = config->value(kBTrackWidth, dBTrackWidth).toInt();
    config->endGroup();

    return width;
}

/*
 * Setter for bar time width.
 *
 * :param width: width
 */
void Config::BTimeWidth(int width)
{
    config->beginGroup(kBar);
    config->setValue(kBTimeWidth, width);
    config->endGroup();
}

/*
 * Getter for bar time width.
 *
 * :return: width
 */
int Config::BTimeWidth()
{
    config->beginGroup(kBar);
    int width = config->value(kBTimeWidth, dBTimeWidth).toInt();
    config->endGroup();

    return width;
}

/*
 * Checks if section contains key.
 *
 * :param section: section
 * :param key: key
 * :return: exists
 */
bool Config::sectionContains(const QString &section, const QString &key)
{
    config->beginGroup(section);
    bool contains = config->contains(key);
    config->endGroup();

    return contains;
}

/*
 * Settings pointer which gets created
 * in create() function. Its parent will
 * be the application so we do not have to
 * worry about freeing it.
 */
QSettings * Config::config         = nullptr;

/*
 * The following variables are groups
 * within the config.
 */
const QString Config::kApp         = "App";
const QString Config::kShortcut    = "Shortcut";
const QString Config::kPlayer      = "Player";
const QString Config::kLibrary     = "Library";
const QString Config::kBar         = "Bar";

/*
 * The following variables with k prefix
 * are keys used in config.
 */
const QString Config::kALog        = "Log";
const QString Config::kAFontSize   = "FontSize";
const QString Config::kSPlayPause  = "PlayPause";
const QString Config::kSNext       = "Next";
const QString Config::kSPrevious   = "Previous";
const QString Config::kSVolumeUp   = "VolumeUp";
const QString Config::kSVolumeDown = "VolumeDown";
const QString Config::kPVolume     = "Volume";
const QString Config::kPShuffle    = "Shuffle";
const QString Config::kPLoop       = "Loop";
const QString Config::kLPath       = "Path";
const QString Config::kLItemHeight = "ItemHeight";
const QString Config::kBHeight     = "Height";
const QString Config::kBSpacing    = "Spacing";
const QString Config::kBCoverSize  = "CoverSize";
const QString Config::kBIconSize   = "IconSize";
const QString Config::kBTrackWidth = "TrackWidth";
const QString Config::kBTimeWidth  = "TimeWidth";

/*
 * The following variables with d prefix
 * are default values used in config.
 */
const bool Config::dALog           = true;
const double Config::dAFontSize    = 10.25;
const QString Config::dSPlayPause  = "Ctrl+F11";
const QString Config::dSNext       = "Ctrl+F12";
const QString Config::dSPrevious   = "Ctrl+F10";
const QString Config::dSVolumeUp   = "Ctrl+F8";
const QString Config::dSVolumeDown = "Ctrl+F7";
const int Config::dPVolume         = 25;
const bool Config::dPShuffle       = false;
const bool Config::dPLoop          = false;
const QString Config::dLPath       = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
const int Config::dLItemHeight     = 50;
const int Config::dBHeight         = 68;
const int Config::dBSpacing        = 10;
const int Config::dBCoverSize      = 48;
const int Config::dBIconSize       = 33;
const int Config::dBTrackWidth     = 240;
const int Config::dBTimeWidth      = 50;
