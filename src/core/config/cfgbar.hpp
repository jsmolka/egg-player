#ifndef CFGBAR_HPP
#define CFGBAR_HPP

#include "core/config/cfgbase.hpp"

namespace cfg
{
class Bar : public Base
{
public:
    using Base::Base;

    void setDefaults() override;

    void setGrooveHeight(int height);
    int grooveHeight() const;

    void setHandleSize(int size);
    int handleSize() const;

    void setHeight(int height);
    int height() const;

    void setIconSize(int size);
    int iconSize() const;

    void setMargin(int margin);
    int margin() const;

    void setSpacing(int spacing);
    int spacing() const;

    void setTimeWidth(int width);
    int timeWidth() const;

    void setTrackWidth(int width);
    int trackWidth() const;

    int coverSize() const;
};
}

#endif // CFGBAR_HPP
