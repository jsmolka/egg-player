#include "configplayer.hpp"

ConfigPlayer::ConfigPlayer()
{

}

ConfigPlayer::ConfigPlayer(const QJsonObject &object)
    : ConfigItem(object)
{

}

ConfigPlayer::~ConfigPlayer()
{

}

void ConfigPlayer::setDefaults()
{
    setDefault("loop", false);
    setDefault("shuffle", false);
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

void ConfigPlayer::setVolume(int volume)
{
    set("volume", volume);
}

int ConfigPlayer::volume()
{
    return get("volume").toInt();
}
