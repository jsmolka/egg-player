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
 * Setter for log.
 *
 * :param log: log
 */
void Config::setLog(bool log)
{
    config->setValue(kLog, log);
}

/*
 * Getter for log.
 *
 * :return: log or default
 */
bool Config::log() const
{
    return config->value(kLog, dLog).toBool();
}

/*
 * Setter for font size.
 *
 * :param size: size
 */
void Config::setFontSize(double size)
{
    config->setValue(kFontSize, size);
}

/*
 * Getter for font size.
 *
 * :return: size or default
 */
double Config::fontSize() const
{
    return config->value(kFontSize, dFontSize).toDouble();
}

/*
 * Setter for EggPlayer library.
 *
 * :param string: path
 */
void Config::setEpLibrary(const QString &path)
{
    config->setValue(kEpLibrary, path);
}

/*
 * Getter for EggPlayer library.
 *
 * :return: path or default
 */
QString Config::epLibrary() const
{
    return config->value(kEpLibrary, dEpLibrary).toString();
}

/*
 * Setter for EggPlayer volume.
 *
 * :param volume: volume
 */
void Config::setEpVolume(int volume)
{
    config->setValue(kEpVolume, volume);
}

/*
 * Getter for EggPlayer volume.
 *
 * :return: volume or default
 */
int Config::epVolume() const
{
    return config->value(kEpVolume, dEpVolume).toInt();
}

/*
 * Setter for MusicLibrary SongInfo height.
 *
 * :param height: height
 */
void Config::setMlSongInfoHeight(int height)
{
    config->setValue(kMlSongInfoHeight, height);
}

/*
 * Getter for MusicLibrary SongInfo height.
 *
 * :return: height or default
 */
int Config::mlSongInfoHeight() const
{
    return config->value(kMlSongInfoHeight, dMlSongInfoHeight).toDouble();
}

/*
 * Setter for MusicBar height.
 *
 * :param height: height
 */
void Config::setMbHeight(int height)
{
    config->setValue(kMbHeight, height);
}

/*
 * Getter for MusicBar height.
 *
 * :result: height or default
 */
int Config::mbHeight() const
{
    return config->value(kMbHeight, dMbHeight).toInt();
}

/*
 * Setter for MusicBar spacing.
 *
 * :param spacing: spacing
 */
void Config::setMbSpacing(int spacing)
{
    config->setValue(kMbSpacing, spacing);
}

/*
 * Getter for MusicBar spacing.
 *
 * :return: spacing or default
 */
int Config::mbSpacing() const
{
    return config->value(kMbSpacing, dMbSpacing).toInt();
}

/*
 * Setter for MusicBar cover size.
 *
 * :param size: size
 */
void Config::setMbCoverSize(int size)
{
    config->setValue(kMbCoverSize, size);
}

/*
 * Getter for MusicBar cover size.
 *
 * :return: size or default
 */
int Config::mbCoverSize() const
{
    return config->value(kMbCoverSize, dMbCoverSize).toInt();
}

/*
 * Setter for MusicBar icon size.
 *
 * :param size: size
 */
void Config::setMbIconSize(int size)
{
    config->setValue(kMbIconSize, size);
}

/*
 * Getter for MusicBar icon size.
 *
 * :return: size or default
 */
int Config::mbIconSize() const
{
    return config->value(kMbIconSize, dMbIconSize).toInt();
}

/*
 * Setter for MusicBar track label width.
 *
 * :param width: width
 */
void Config::setMbTrackLabelWidth(int width)
{
    config->setValue(kMbTrackLabelWidth, width);
}

/*
 * Getter for MusicBar track label width.
 *
 * :return: width or default
 */
int Config::mbTrackLabelWidth() const
{
    return config->value(kMbTrackLabelWidth, dMbTrackLabelWidth).toInt();
}

/*
 * Setter for MusicBar time label width.
 *
 * :param width: width
 */
void Config::setMbTimeLabelWidth(int width)
{
    config->setValue(kMbTimeLabelWidth, width);
}

/*
 * Getter for MusicBar time label width.
 *
 * :return: width or default
 */
int Config::mbTimeLabelWidth() const
{
    return config->value(kMbTimeLabelWidth, dMbTimeLabelWidth).toInt();
}

/*
 * Settings pointer which gets created
 * in create() function. Its parent will
 * be the application so we do not have to
 * worry about freeing it.
 */
QSettings * Config::config             = nullptr;

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
