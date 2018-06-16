#ifndef CONFIGPLAYER_HPP
#define CONFIGPLAYER_HPP

#include "configitem.hpp"

class ConfigPlayer : public ConfigItem
{
public:
    ConfigPlayer();
    ConfigPlayer(const QJsonObject &object);
    ~ConfigPlayer();

    void setDefaults() override;

    void setLoop(bool loop);
    bool loop();

    void setShuffle(bool shuffle);
    bool shuffle();

    void setVolume(int volume);
    int volume();
};

#endif // CONFIGPLAYER_HPP
