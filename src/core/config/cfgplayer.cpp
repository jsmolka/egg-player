#include "cfgplayer.hpp"

void cfg::Player::setDefaults()
{
    setDefault("loop", false);
    setDefault("previousLimit", 3);
    setDefault("shuffle", false);
    setDefault("updateInterval", 50);
    setDefault("volume", 25);
    setDefault("volumeQuotient", 1000);
}

void cfg::Player::setLoop(bool loop)
{
    set("loop", loop);
}

bool cfg::Player::loop() const
{
    return get("loop").toBool();
}

void cfg::Player::setPreviousLimit(int limit)
{
    set("previousLimit", limit);
}

int cfg::Player::previousLimit() const
{
    return get("previousLimit").toInt();
}

void cfg::Player::setShuffle(bool shuffle)
{
    set("shuffle", shuffle);
}

bool cfg::Player::shuffle() const
{
    return get("shuffle").toBool();
}

void cfg::Player::setUpdateInterval(int interval)
{
    set("updateInterval", interval);
}

int cfg::Player::updateInterval() const
{
    return get("updateInterval").toInt();
}

void cfg::Player::setVolume(int volume)
{
    set("volume", volume);
}

int cfg::Player::volume() const
{
    return get("volume").toInt();
}

void cfg::Player::setVolumeQuotient(int quotient)
{
    set("volumeQuotient", quotient);
}

int cfg::Player::volumeQuotient() const
{
    return get("volumeQuotient").toInt();
}
