#include "config.hpp"

/*
 * Creates settings and sets all non
 * existing keys to default value.
 */
void Config::create()
{
    if (!settings)
    {
        settings = new QSettings(CFG_PATH, QSettings::IniFormat, QApplication::instance());

        if (!contains(kLog))
            setLog(dLog);

        if (!contains(kFontSize))
            setFontSize(dFontSize);

        if (!contains(kEpLibrary))
            setEpLibrary(dEpLibrary);

        if (!contains(kEpVolume))
            setEpVolume(dEpVolume);

        if (!contains(kMlSongInfoHeight))
            setMlSongInfoHeight(dMlSongInfoHeight);

        if (!contains(kMbHeight))
            setMbHeight(dMbHeight);

        if (!contains(kMbSpacing))
            setMbSpacing(dMbSpacing);

        if (!contains(kMbCoverSize))
            setMbCoverSize(dMbCoverSize);

        if (!contains(kMbIconSize))
            setMbIconSize(dMbIconSize);

        if (!contains(kMbTrackLabelWidth))
            setMbTrackLabelWidth(dMbTrackLabelWidth);

        if (!contains(kMbTimeLabelWidth))
            setMbTimeLabelWidth(dMbTimeLabelWidth);
    }
}

/*
 * Checks if config contains key.
 *
 * :param key: key
 * :return: exists
 */
bool Config::contains(const QString &key)
{
    return settings->contains(key);
}

/*
 * Setter for log.
 *
 * :param log: log
 */
void Config::setLog(bool log)
{
    settings->setValue(kLog, log);
}

/*
 * Getter for log.
 *
 * :return: log or default
 */
bool Config::log()
{
    return settings->value(kLog, dLog).toBool();
}

/*
 * Setter for font size.
 *
 * :param size: size
 */
void Config::setFontSize(double size)
{
    settings->setValue(kFontSize, size);
}

/*
 * Getter for font size.
 *
 * :return: size or default
 */
double Config::fontSize()
{
    return settings->value(kFontSize, dFontSize).toDouble();
}

/*
 * Setter for egg player library.
 *
 * :param string: path
 */
void Config::setEpLibrary(const QString &path)
{
    settings->setValue(kEpLibrary, path);
}

/*
 * Getter for egg player library.
 *
 * :return: path or default
 */
QString Config::epLibrary()
{
    return settings->value(kEpLibrary, dEpLibrary).toString();
}

/*
 * Setter for egg player volume.
 *
 * :param volume: volume
 */
void Config::setEpVolume(int volume)
{
    settings->setValue(kEpVolume, volume);
}

/*
 * Getter for egg player volume.
 *
 * :return: volume or default
 */
int Config::epVolume()
{
    return settings->value(kEpVolume, dEpVolume).toInt();
}

/*
 * Setter for music library song info height.
 *
 * :param height: height
 */
void Config::setMlSongInfoHeight(int height)
{
    settings->setValue(kMlSongInfoHeight, height);
}

/*
 * Getter for music library song info height.
 *
 * :return: height or default
 */
int Config::mlSongInfoHeight()
{
    return settings->value(kMlSongInfoHeight, dMlSongInfoHeight).toDouble();
}

/*
 * Setter for music bar height.
 *
 * :param height: height
 */
void Config::setMbHeight(int height)
{
    settings->setValue(kMbHeight, height);
}

/*
 * Getter for music bar height.
 *
 * :result: height or default
 */
int Config::mbHeight()
{
    return settings->value(kMbHeight, dMbHeight).toInt();
}

/*
 * Setter for music bar spacing.
 *
 * :param spacing: spacing
 */
void Config::setMbSpacing(int spacing)
{
    settings->setValue(kMbSpacing, spacing);
}

/*
 * Getter for music bar spacing.
 *
 * :return: spacing or default
 */
int Config::mbSpacing()
{
    return settings->value(kMbSpacing, dMbSpacing).toInt();
}

/*
 * Setter for music bar cover size.
 *
 * :param size: size
 */
void Config::setMbCoverSize(int size)
{
    settings->setValue(kMbCoverSize, size);
}

/*
 * Getter for music bar cover size.
 *
 * :return: size or default
 */
int Config::mbCoverSize()
{
    return settings->value(kMbCoverSize, dMbCoverSize).toInt();
}

/*
 * Setter for music bar icon size.
 *
 * :param size: size
 */
void Config::setMbIconSize(int size)
{
    settings->setValue(kMbIconSize, size);
}

/*
 * Getter for music bar icon size.
 *
 * :return: size or default
 */
int Config::mbIconSize()
{
    return settings->value(kMbIconSize, dMbIconSize).toInt();
}

/*
 * Setter for music bar track label width.
 *
 * :param width: width
 */
void Config::setMbTrackLabelWidth(int width)
{
    settings->setValue(kMbTrackLabelWidth, width);
}

/*
 * Getter for music bar track label width.
 *
 * :return: width or default
 */
int Config::mbTrackLabelWidth()
{
    return settings->value(kMbTrackLabelWidth, dMbTrackLabelWidth).toInt();
}

/*
 * Setter for music bar time label width.
 *
 * :param width: width
 */
void Config::setMbTimeLabelWidth(int width)
{
    settings->setValue(kMbTimeLabelWidth, width);
}

/*
 * Getter for music bar time label width.
 *
 * :return: width or default
 */
int Config::mbTimeLabelWidth()
{
    return settings->value(kMbTimeLabelWidth, dMbTimeLabelWidth).toInt();
}

/*
 * Settings pointer which gets created
 * in create() function. Its parent will
 * be the application so we do not have to
 * worry about freeing it.
 */
QSettings * Config::settings             = nullptr;

/*
 * The following variables with k prefix
 * are keys used in config.
 */
const QString Config::kLog               = "App/Log";
const QString Config::kFontSize          = "App/FontSize";
const QString Config::kEpLibrary         = "Player/Library";
const QString Config::kEpVolume          = "Player/Volume";
const QString Config::kMlSongInfoHeight  = "MusicLibrary/SongInfoHeight";
const QString Config::kMbHeight          = "MusicBar/Height";
const QString Config::kMbSpacing         = "MusicBar/Spacing";
const QString Config::kMbCoverSize       = "MusicBar/CoverSize";
const QString Config::kMbIconSize        = "MusicBar/IconSize";
const QString Config::kMbTrackLabelWidth = "MusicBar/TrackLabelWidth";
const QString Config::kMbTimeLabelWidth  = "MusicBar/TimeLabelWidth";

/*
 * The following variables with d prefix
 * are default values used in config.
 */
const bool Config::dLog                  = true;
const double Config::dFontSize           = 10.25;
const QString Config::dEpLibrary         = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
const int Config::dEpVolume              = 25;
const int Config::dMlSongInfoHeight      = 50;
const int Config::dMbHeight              = 68;
const int Config::dMbSpacing             = 10;
const int Config::dMbCoverSize           = 48;
const int Config::dMbIconSize            = 35;
const int Config::dMbTrackLabelWidth     = 240;
const int Config::dMbTimeLabelWidth      = 50;
