#include "configplayer.hpp"

void ConfigPlayer::setDefaults()
{
    setDefault("loop", false);
    setDefault("shuffle", false);
    setDefault("updateInterval", 50);
    setDefault("volume", 25);
}

void ConfigPlayer::setLoop(bool loop)
{
    set("loop", loop);
}

bool ConfigPlayer::loop()
{
    return get("loop").toBool();
}

void ConfigPlayer::setShuffle(bool shuffle)
{
    set("shuffle", shuffle);
}

bool ConfigPlayer::shuffle()
{
    return get("shuffle").toBool();
}

void ConfigPlayer::setUpdateInterval(int interval)
{
    set("updateInterval", interval);
}

int ConfigPlayer::updateInterval()
{
    return get("updateInterval").toInt();
}

void ConfigPlayer::setVolume(int volume)
{
    set("volume", volume);
}

int ConfigPlayer::volume()
{
    return get("volume").toInt();
}
