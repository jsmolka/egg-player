#include "configplayer.hpp"

void ConfigPlayer::setDefaults()
{
    setDefault("loop", false);
    setDefault("previousLimit", 3);
    setDefault("shuffle", false);
    setDefault("updateInterval", 50);
    setDefault("volume", 25);
    setDefault("volumeQuotient", 1000);
}

void ConfigPlayer::setLoop(bool loop)
{
    set("loop", loop);
}

bool ConfigPlayer::loop() const
{
    return get("loop").toBool();
}

void ConfigPlayer::setPreviousLimit(int limit)
{
    set("previousLimit", limit);
}

int ConfigPlayer::previousLimit() const
{
    return get("previousLimit").toInt();
}

void ConfigPlayer::setShuffle(bool shuffle)
{
    set("shuffle", shuffle);
}

bool ConfigPlayer::shuffle() const
{
    return get("shuffle").toBool();
}

void ConfigPlayer::setUpdateInterval(int interval)
{
    set("updateInterval", interval);
}

int ConfigPlayer::updateInterval() const
{
    return get("updateInterval").toInt();
}

void ConfigPlayer::setVolume(int volume)
{
    set("volume", volume);
}

int ConfigPlayer::volume() const
{
    return get("volume").toInt();
}

void ConfigPlayer::setVolumeQuotient(int quotient)
{
    set("volumeQuotient", quotient);
}

int ConfigPlayer::volumeQuotient() const
{
    return get("volumeQuotient").toInt();
}
