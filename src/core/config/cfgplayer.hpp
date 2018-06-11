#ifndef CFGPLAYER_HPP
#define CFGPLAYER_HPP

#include "cfgabstract.hpp"

class CfgPlayer : public CfgAbstract
{
public:
    CfgPlayer();
    CfgPlayer(QJsonObject object);

    void setDefaults() override;

    void setLoop(bool loop);
    bool loop();

    void setShuffle(bool shuffle);
    bool shuffle();

    void setVolume(int volume);
    int volume();
};

#endif // CFGPLAYER_HPP
