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
 * Checks if config contains keys.
 *
 * :param key: key to look up
 * :return: exists
 */
bool Config::contains(const QString &key)
{
    return settings->contains(key);
}

/*
 * Log setter.
 *
 * :param log: store logs
 */
void Config::setLog(bool log)
{
    settings->setValue(kLog, log);
}

/*
 * Log getter.
 *
 * :return: store logs or default
 */
bool Config::log()
{
    return settings->value(kLog, dLog).toBool();
}

/*
 * Font size setter.
 *
 * :param size: font size
 */
void Config::setFontSize(double size)
{
    settings->setValue(kFontSize, size);
}

/*
 * Font size getter.
 *
 * :return: font size or default
 */
double Config::fontSize()
{
    return settings->value(kFontSize, dFontSize).toDouble();
}

/*
 * Egg player libaray setter.
 *
 * :param string: path
 */
void Config::setEpLibrary(const QString &path)
{
    settings->setValue(kEpLibrary, path);
}

/*
 * Egg player library getter.
 *
 * :return: path or default
 */
QString Config::epLibrary()
{
    return settings->value(kEpLibrary, dEpLibrary).toString();
}

/*
 * Egg player volume setter.
 *
 * :param volume: volume
 */
void Config::setEpVolume(int volume)
{
    settings->setValue(kEpVolume, volume);
}

/*
 * Egg player volume getter.
 *
 * :return: volume or default
 */
int Config::epVolume()
{
    return settings->value(kEpVolume, dEpVolume).toInt();
}

/*
 * Music library song info height setter.
 *
 * :param height: height
 */
void Config::setMlSongInfoHeight(int height)
{
    settings->setValue(kMlSongInfoHeight, height);
}

/*
 * Music library song infor height getter.
 *
 * :return: height or default.
 */
int Config::mlSongInfoHeight()
{
    return settings->value(kMlSongInfoHeight, dMlSongInfoHeight).toDouble();
}

/*
 * Music bar height setter.
 *
 * :param height: height
 */
void Config::setMbHeight(int height)
{
    settings->setValue(kMbHeight, height);
}

/*
 * Music bar height getter.
 *
 * :result: height or default
 */
int Config::mbHeight()
{
    return settings->value(kMbHeight, dMbHeight).toInt();
}

/*
 * Music bar spacing setter.
 *
 * :param spacing: spacing
 */
void Config::setMbSpacing(int spacing)
{
    settings->setValue(kMbSpacing, spacing);
}

/*
 * Music bar spacing getter.
 *
 * :return: spacing or default
 */
int Config::mbSpacing()
{
    return settings->value(kMbSpacing, dMbSpacing).toInt();
}

/*
 * Music bar cover size setter.
 *
 * :param size: size
 */
void Config::setMbCoverSize(int size)
{
    settings->setValue(kMbCoverSize, size);
}

/*
 * Music bar cover size getter.
 *
 * :return: size or default
 */
int Config::mbCoverSize()
{
    return settings->value(kMbCoverSize, dMbCoverSize).toInt();
}

/*
 * Music bar icon size setter.
 *
 * :param size: size
 */
void Config::setMbIconSize(int size)
{
    settings->setValue(kMbIconSize, size);
}

/*
 * Music bar icon size getter.
 *
 * :return: size or default
 */
int Config::mbIconSize()
{
    return settings->value(kMbIconSize, dMbIconSize).toInt();
}

/*
 * Music bar track label width setter.
 *
 * :param width: width
 */
void Config::setMbTrackLabelWidth(int width)
{
    settings->setValue(kMbTrackLabelWidth, width);
}

/*
 * Music bar track label width getter.
 *
 * :return: width or default
 */
int Config::mbTrackLabelWidth()
{
    return settings->value(kMbTrackLabelWidth, dMbTrackLabelWidth).toInt();
}

/*
 * Music bar time label width setter.
 *
 * :param width: width
 */
void Config::setMbTimeLabelWidth(int width)
{
    settings->setValue(kMbTimeLabelWidth, width);
}

/*
 * Music bar time label width getter.
 *
 * :return: width or default
 */
int Config::mbTimeLabelWidth()
{
    return settings->value(kMbTimeLabelWidth, dMbTimeLabelWidth).toInt();
}

/*
 * Settings pointer which gets
 * creates one time. Its parent is
 * the application so we do not have
 * to worry about freeing.
 */
QSettings * Config::settings             = nullptr;

/*
 * The following values with k
 * prefix are key used in config.
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
 * The following values with d prefix
 * are default values use in config.
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
