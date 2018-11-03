#ifndef CFGBARSLIDER_HPP
#define CFGBARSLIDER_HPP

#include "core/config/cfgbase.hpp"

namespace cfg
{
namespace bar
{
class Slider : public Base
{
public:
    void loadObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    void setGrooveHeight(int height);
    int grooveHeight() const;

    void setHandleSize(int size);
    int handleSize() const;
};
}
}

#endif // CFGBARSLIDER_HPP
