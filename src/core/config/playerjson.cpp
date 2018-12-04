#include "playerjson.hpp"

void cfg::PlayerJson::loadFromObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::PlayerJson::toObject() const
{
    return object();
}

void cfg::PlayerJson::setDefaults()
{
    setDefault("loop", false);
    setDefault("previousLimit", 3);
    setDefault("shuffle", false);
    setDefault("updateInterval", 50);
    setDefault("volume", 25);
    setDefault("volumeQuotient", 1000);
}

void cfg::PlayerJson::setLoop(bool loop)
{
    set("loop", loop);
}

bool cfg::PlayerJson::loop() const
{
    return get("loop").toBool();
}

void cfg::PlayerJson::setPreviousLimit(int limit)
{
    set("previousLimit", limit);
}

int cfg::PlayerJson::previousLimit() const
{
    return get("previousLimit").toInt();
}

void cfg::PlayerJson::setShuffle(bool shuffle)
{
    set("shuffle", shuffle);
}

bool cfg::PlayerJson::shuffle() const
{
    return get("shuffle").toBool();
}

void cfg::PlayerJson::setUpdateInterval(int interval)
{
    set("updateInterval", interval);
}

int cfg::PlayerJson::updateInterval() const
{
    return get("updateInterval").toInt();
}

void cfg::PlayerJson::setVolume(int volume)
{
    set("volume", volume);
}

int cfg::PlayerJson::volume() const
{
    return get("volume").toInt();
}

void cfg::PlayerJson::setVolumeQuotient(int quotient)
{
    set("volumeQuotient", quotient);
}

int cfg::PlayerJson::volumeQuotient() const
{
    return get("volumeQuotient").toInt();
}
