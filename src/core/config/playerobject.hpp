#ifndef CFG_PLAYEROBJECT_HPP
#define CFG_PLAYEROBJECT_HPP

#include "core/config/jsonobject.hpp"

namespace cfg
{

class PlayerObject : public JsonObject
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

#endif // CFG_PLAYEROBJECT_HPP
