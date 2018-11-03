#ifndef CFGPLAYER_HPP
#define CFGPLAYER_HPP

#include "core/config/cfgbase.hpp"

namespace cfg
{
class Player : public Base
{
public:
    void loadObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    void setLoop(bool loop);
    bool loop() const;

    void setPreviousLimit(int limit);
    int previousLimit() const;

    void setShuffle(bool shuffle);
    bool shuffle() const;

    void setUpdateInterval(int interval);
    int updateInterval() const;

    void setVolume(int volume);
    int volume() const;

    void setVolumeQuotient(int quotient);
    int volumeQuotient() const;
};
}

#endif // CFGPLAYER_HPP
