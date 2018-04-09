#include "config.hpp"

QSettings *cfg = 0;

void Config::load()
{
    QCoreApplication *app = QApplication::instance();

    cfg = new QSettings(CFG_PATH, QSettings::IniFormat, app);
    if (!contains(KEY_EGGPLAYER_LIBRARY))
        setEggPlayerLibrary(DEF_EGGPLAYER_LIBRARY);
    if (!contains(KEY_EGGPLAYER_VOLUME))
        setEggPlayerVolume(DEF_EGGPLAYER_VOLUME);
    if (!contains(KEY_MUSICBAR_HEIGHT))
        setMusicBarHeight(DEF_MUSICBAR_HEIGHT);
    if (!contains(KEY_MUSICBAR_SPACING))
        setMusicBarSpacing(DEF_MUSICBAR_SPACING);
}

bool Config::contains(const QString &key)
{
    return cfg->contains(key);
}

void Config::setEggPlayerLibrary(const QString &string)
{
    cfg->setValue(KEY_EGGPLAYER_LIBRARY, string);
}

QString Config::eggPlayerLibrary()
{
    return cfg->value(KEY_EGGPLAYER_LIBRARY).toString();
}

void Config::setEggPlayerVolume(int volume)
{
    cfg->setValue(KEY_EGGPLAYER_VOLUME, volume);
}

int Config::eggPlayerVolume()
{
    return cfg->value(KEY_EGGPLAYER_VOLUME).toInt();
}

void Config::setMusicBarHeight(int height)
{
    cfg->setValue(KEY_MUSICBAR_HEIGHT, height);
}

int Config::musicBarHeight()
{
    return cfg->value(KEY_MUSICBAR_HEIGHT).toInt();
}

void Config::setMusicBarSpacing(int spacing)
{
    cfg->setValue(KEY_MUSICBAR_SPACING, spacing);
}

int Config::musicBarSpacing()
{
    return cfg->value(KEY_MUSICBAR_SPACING).toInt();
}
