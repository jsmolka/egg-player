#ifndef CONFIGPLAYER_HPP
#define CONFIGPLAYER_HPP

#include "configitem.hpp"

class ConfigPlayer : public ConfigItem
{
public:
    using ConfigItem::ConfigItem;

    void setDefaults() override;

    void setLoop(bool loop);
    bool loop() const;

    void setShuffle(bool shuffle);
    bool shuffle() const;

    void setUpdateInterval(int interval);
    int updateInterval() const;

    void setVolume(int volume);
    int volume() const;

    void setVolumeQuotient(int quotient);
    int volumeQuotient() const;
};

#endif // CONFIGPLAYER_HPP
