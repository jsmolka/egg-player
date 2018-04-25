#include "config.hpp"

/*
 * Creates settings and sets all non
 * existing keys to their default value.
 */
void Config::create()
{
    if (config)
        return;

    config = new QSettings(CFG_PATH, QSettings::IniFormat, QApplication::instance());

    if (!contains(kALog))
        ALog(dALog);

    if (!contains(kAFontSize))
        AFontSize(dAFontSize);

    if (!contains(kPVolume))
        PVolume(dPVolume);

    if (!contains(kPShuffle))
        PShuffle(dPShuffle);

    if (!contains(kPLoop))
        PLoop(dPLoop);

    if (!contains(kLPath))
        LPath(dLPath);

    if (!contains(kLItemHeight))
        LItemHeight(dLItemHeight);

    if (!contains(kBHeight))
        BHeight(dBHeight);

    if (!contains(kBSpacing))
        BSpacing(dBSpacing);

    if (!contains(kBCoverSize))
        BCoverSize(dBCoverSize);

    if (!contains(kBIconSize))
        BIconSize(dBIconSize);

    if (!contains(kBTrackWidth))
        BTrackWidth(dBTrackWidth);

    if (!contains(kBTimeWidth))
        BTimeWidth(dBTimeWidth);
}

/*
 * Checks if config contains key.
 *
 * :param key: key
 * :return: exists
 */
bool Config::contains(const QString &key)
{
    return config->contains(key);
}

/*
 * Setter for app log.
 *
 * :param log: log
 */
void Config::ALog(bool log)
{
    config->setValue(kALog, log);
}

/*
 * Getter for app log.
 *
 * :return: log
 */
bool Config::ALog()
{
    return config->value(kALog, dALog).toBool();
}

/*
 * Setter for app font size.
 *
 * :param size: size
 */
void Config::AFontSize(double size)
{
    config->setValue(kAFontSize, size);
}

/*
 * Getter for app font size.
 *
 * :return: size
 */
double Config::AFontSize()
{
    return config->value(kAFontSize, dAFontSize).toDouble();
}

/*
 * Setter for player volume.
 *
 * :param volume: volume
 */
void Config::PVolume(int volume)
{
    config->setValue(dLPath, volume);
}

/*
 * Getter for player volume.
 *
 * :return: volume
 */
int Config::PVolume()
{
    return config->value(kPVolume, dPVolume).toInt();
}

/*
 * Setter for player shuffle.
 *
 * :param shuffle: shuffle
 */
void Config::PShuffle(bool shuffle)
{
    config->setValue(kPShuffle, shuffle);
}

/*
 * Getter for player shuffle.
 *
 * :return: shuffle
 */
bool Config::PShuffle()
{
    return config->value(kPShuffle, dPShuffle).toBool();
}

/*
 * Setter for player loop.
 *
 * :param loop: loop
 */
void Config::PLoop(bool loop)
{
    config->setValue(kPLoop, loop);
}

/*
 * Getter for player loop.
 *
 * :return: loop
 */
bool Config::PLoop()
{
    return config->value(kPLoop, dPLoop).toBool();
}

/*
 * Setter for library path.
 *
 * :param string: path
 */
void Config::LPath(const QString &path)
{
    config->setValue(kLPath, path);
}

/*
 * Getter for library path.
 *
 * :return: path
 */
QString Config::LPath()
{
    return config->value(kLPath, dLPath).toString();
}

/*
 * Setter for library item height.
 *
 * :param height: height
 */
void Config::LItemHeight(int height)
{
    config->setValue(kLItemHeight, height);
}

/*
 * Getter for library item height.
 *
 * :return: height
 */
int Config::LItemHeight()
{
    return config->value(kLItemHeight, dLItemHeight).toDouble();
}

/*
 * Setter for bar height.
 *
 * :param height: height
 */
void Config::BHeight(int height)
{
    config->setValue(kBHeight, height);
}

/*
 * Getter for bar height.
 *
 * :result: height
 */
int Config::BHeight()
{
    return config->value(kBHeight, dBHeight).toInt();
}

/*
 * Setter for bar spacing.
 *
 * :param spacing: spacing
 */
void Config::BSpacing(int spacing)
{
    config->setValue(kBSpacing, spacing);
}

/*
 * Getter for bar spacing.
 *
 * :return: spacing
 */
int Config::BSpacing()
{
    return config->value(kBSpacing, dBSpacing).toInt();
}

/*
 * Setter for bar cover size.
 *
 * :param size: size
 */
void Config::BCoverSize(int size)
{
    config->setValue(kBCoverSize, size);
}

/*
 * Getter for bar cover size.
 *
 * :return: size
 */
int Config::BCoverSize()
{
    return config->value(kBCoverSize, dBCoverSize).toInt();
}

/*
 * Setter for bar icon size.
 *
 * :param size: size
 */
void Config::BIconSize(int size)
{
    config->setValue(kBIconSize, size);
}

/*
 * Getter for bar icon size.
 *
 * :return: size
 */
int Config::BIconSize()
{
    return config->value(kBIconSize, dBIconSize).toInt();
}

/*
 * Setter for bar track width.
 *
 * :param width: width
 */
void Config::BTrackWidth(int width)
{
    config->setValue(kBTrackWidth, width);
}

/*
 * Getter for bar track width.
 *
 * :return: width
 */
int Config::BTrackWidth()
{
    return config->value(kBTrackWidth, dBTrackWidth).toInt();
}

/*
 * Setter for bar time width.
 *
 * :param width: width
 */
void Config::BTimeWidth(int width)
{
    config->setValue(kBTimeWidth, width);
}

/*
 * Getter for bar time width.
 *
 * :return: width
 */
int Config::BTimeWidth()
{
    return config->value(kBTimeWidth, dBTimeWidth).toInt();
}

/*
 * Settings pointer which gets created
 * in create() function. Its parent will
 * be the application so we do not have to
 * worry about freeing it.
 */
QSettings * Config::config         = nullptr;

/*
 * The following variables with k prefix
 * are keys used in config.
 */
const QString Config::kALog        = "App/Log";
const QString Config::kAFontSize   = "App/FontSize";
const QString Config::kPVolume     = "Player/Volume";
const QString Config::kPShuffle    = "Player/Shuffle";
const QString Config::kPLoop       = "Player/Loop";
const QString Config::kLPath       = "Library/Path";
const QString Config::kLItemHeight = "Library/ItemHeight";
const QString Config::kBHeight     = "Bar/Height";
const QString Config::kBSpacing    = "Bar/Spacing";
const QString Config::kBCoverSize  = "Bar/CoverSize";
const QString Config::kBIconSize   = "Bar/IconSize";
const QString Config::kBTrackWidth = "Bar/TrackWidth";
const QString Config::kBTimeWidth  = "Bar/TimeWidth";

/*
 * The following variables with d prefix
 * are default values used in config.
 */
const bool Config::dALog           = true;
const double Config::dAFontSize    = 10.25;
const int Config::dPVolume         = 25;
const bool Config::dPShuffle       = false;
const bool Config::dPLoop          = false;
const QString Config::dLPath       = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
const int Config::dLItemHeight     = 50;
const int Config::dBHeight         = 68;
const int Config::dBSpacing        = 10;
const int Config::dBCoverSize      = 48;
const int Config::dBIconSize       = 35;
const int Config::dBTrackWidth     = 240;
const int Config::dBTimeWidth      = 50;
