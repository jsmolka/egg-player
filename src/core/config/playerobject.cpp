#include "playerobject.hpp"

void cfg::PlayerObject::loadObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::PlayerObject::toObject() const
{
    return object();
}

void cfg::PlayerObject::setDefaults()
{
    setDefault("loop", false);
    setDefault("previousLimit", 3);
    setDefault("shuffle", false);
    setDefault("updateInterval", 50);
    setDefault("volume", 25);
    setDefault("volumeQuotient", 1000);
}

void cfg::PlayerObject::setLoop(bool loop)
{
    set("loop", loop);
}

bool cfg::PlayerObject::loop() const
{
    return get("loop").toBool();
}

void cfg::PlayerObject::setPreviousLimit(int limit)
{
    set("previousLimit", limit);
}

int cfg::PlayerObject::previousLimit() const
{
    return get("previousLimit").toInt();
}

void cfg::PlayerObject::setShuffle(bool shuffle)
{
    set("shuffle", shuffle);
}

bool cfg::PlayerObject::shuffle() const
{
    return get("shuffle").toBool();
}

void cfg::PlayerObject::setUpdateInterval(int interval)
{
    set("updateInterval", interval);
}

int cfg::PlayerObject::updateInterval() const
{
    return get("updateInterval").toInt();
}

void cfg::PlayerObject::setVolume(int volume)
{
    set("volume", volume);
}

int cfg::PlayerObject::volume() const
{
    return get("volume").toInt();
}

void cfg::PlayerObject::setVolumeQuotient(int quotient)
{
    set("volumeQuotient", quotient);
}

int cfg::PlayerObject::volumeQuotient() const
{
    return get("volumeQuotient").toInt();
}
