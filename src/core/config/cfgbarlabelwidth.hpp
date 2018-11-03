#ifndef CFGBARLABELWIDTH_HPP
#define CFGBARLABELWIDTH_HPP

#include "core/config/cfgbase.hpp"

namespace cfg
{
namespace bar
{
class LabelWidth : public Base
{
public:
    void loadObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    void setTime(int width);
    int time() const;

    void setTrack(int width);
    int track() const;
};
}
}

#endif // CFGBARLABELWIDTH_HPP
