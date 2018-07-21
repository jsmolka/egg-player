#ifndef CONFIGPLAYER_HPP
#define CONFIGPLAYER_HPP

#include "configabstract.hpp"

class ConfigPlayer : public ConfigAbstract
{
public:
    using ConfigAbstract::ConfigAbstract;

    void setDefaults() override;

    void setLoop(bool loop);
    bool loop();

    void setShuffle(bool shuffle);
    bool shuffle();

    void setUpdateInterval(int interval);
    int updateInterval();

    void setVolume(int volume);
    int volume();
};

#endif // CONFIGPLAYER_HPP
