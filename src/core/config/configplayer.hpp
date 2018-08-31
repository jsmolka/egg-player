#ifndef CONFIGPLAYER_HPP
#define CONFIGPLAYER_HPP

#include "configitem.hpp"

class ConfigPlayer : public ConfigItem
{
public:
    using ConfigItem::ConfigItem;

    void setDefaults() override;

    void setLoop(bool loop);
    bool loop();

    void setShuffle(bool shuffle);
    bool shuffle();

    void setUpdateInterval(int interval);
    int updateInterval();

    void setVolume(int volume);
    int volume();

    void setVolumeQuotient(int quotient);
    int volumeQuotient();
};

#endif // CONFIGPLAYER_HPP
