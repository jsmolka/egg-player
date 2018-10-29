#ifndef CFGAPP_HPP
#define CFGAPP_HPP

#include "core/config/cfgbase.hpp"

namespace cfg
{
class App : public Base
{
public:
    using Base::Base;

    void setDefaults() override;

    void setFontSize(double size);
    double fontSize() const;

    void setLog(bool log);
    bool log() const;

    void setMinimalHeight(int height);
    int minimalHeight() const;

    void setMinimalWidth(int width);
    int minimalWidth() const;
};
}

#endif // CFGAPP_HPP
