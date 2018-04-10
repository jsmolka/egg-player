#include "config.hpp"

QSettings *cfg = 0;

const QString Config::kEpLibrary         = "Player/Library";
const QString Config::kEpVolume          = "Player/Volume";
const QString Config::kEpFontSize        = "Player/FontSize";
const QString Config::kMlSongInfoHeight  = "MusicLibrary/SongInfoHeight";
const QString Config::kMbHeight          = "MusicBar/Height";
const QString Config::kMbSpacing         = "MusicBar/Spacing";
const QString Config::kMbCoverSize       = "MusicBar/CoverSize";
const QString Config::kMbIconSize        = "MusicBar/IconSize";
const QString Config::kMbTrackLabelWidth = "MusicBar/TrackLabelWidth";
const QString Config::kMbTimeLabelWidth  = "MusicBar/TimeLabelWidth";

const QString Config::dEpLibrary         = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
const int Config::dEpVolume              = 10;
const double Config::dEpFontSize         = 10.25;
const int Config::dMlSongInfoHeight      = 50;
const int Config::dMbHeight              = 68;
const int Config::dMbSpacing             = 10;
const int Config::dMbCoverSize           = 48;
const int Config::dMbIconSize            = 35;
const int Config::dMbTrackLabelWidth     = 240;
const int Config::dMbTimeLabelWidth      = 50;

void Config::load()
{
    QCoreApplication *app = QApplication::instance();

    cfg = new QSettings(CFG_PATH, QSettings::IniFormat, app);
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

bool Config::contains(const QString &key)
{
    return cfg->contains(key);
}

void Config::setEpLibrary(const QString &string)
{
    cfg->setValue(kEpLibrary, string);
}

QString Config::epLibrary()
{
    return cfg->value(kEpLibrary, dEpLibrary).toString();
}

void Config::setEpVolume(int volume)
{
    cfg->setValue(kEpVolume, volume);
}

int Config::epVolume()
{
    return cfg->value(kEpVolume, dEpVolume).toInt();
}

void Config::setEpFontSize(double size)
{
    cfg->setValue(kEpFontSize, size);
}

double Config::epFontSize()
{
    return cfg->value(kEpFontSize, dEpFontSize).toDouble();
}

void Config::setMlSongInfoHeight(int height)
{
    cfg->setValue(kMlSongInfoHeight, height);
}

int Config::mlSongInfoHeight()
{
    return cfg->value(kMlSongInfoHeight, dMlSongInfoHeight).toDouble();
}

void Config::setMbHeight(int height)
{
    cfg->setValue(kMbHeight, height);
}

int Config::mbHeight()
{
    return cfg->value(kMbHeight, dMbHeight).toInt();
}

void Config::setMbSpacing(int spacing)
{
    cfg->setValue(kMbSpacing, spacing);
}

int Config::mbSpacing()
{
    return cfg->value(kMbSpacing, dMbSpacing).toInt();
}

void Config::setMbCoverSize(int size)
{
    cfg->setValue(kMbCoverSize, size);
}

int Config::mbCoverSize()
{
    return cfg->value(kMbCoverSize, dMbCoverSize).toInt();
}

void Config::setMbIconSize(int size)
{
    cfg->setValue(kMbIconSize, size);
}

int Config::mbIconSize()
{
    return cfg->value(kMbIconSize, dMbIconSize).toInt();
}

void Config::setMbTrackLabelWidth(int width)
{
    cfg->setValue(kMbTrackLabelWidth, width);
}

int Config::mbTrackLabelWidth()
{
    return cfg->value(kMbTrackLabelWidth, dMbTrackLabelWidth).toInt();
}

void Config::setMbTimeLabelWidth(int width)
{
    cfg->setValue(kMbTimeLabelWidth, width);
}

int Config::mbTimeLabelWidth()
{
    return cfg->value(kMbTimeLabelWidth, dMbTimeLabelWidth).toInt();
}