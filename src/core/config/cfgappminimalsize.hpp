#ifndef CFGAPPMINIMALSIZE_HPP
#define CFGAPPMINIMALSIZE_HPP

#include "core/config/cfgbase.hpp"

namespace cfg
{
namespace app
{
class MinimalSize : public Base
{
public:
    void loadObject(const QJsonObject &object) override;
    QJsonObject toObject() const override;

    void setDefaults() override;

    void setHeight(int height);
    int height() const;

    void setWidth(int width);
    int width() const;
};
}
}

#endif // CFGAPPMINIMALSIZE_HPP
