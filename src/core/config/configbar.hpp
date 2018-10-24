#ifndef CONFIGBAR_HPP
#define CONFIGBAR_HPP

#include "core/config/configitem.hpp"

class ConfigBar : public ConfigItem
{
public:
    using ConfigItem::ConfigItem;

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

#endif // CONFIGBAR_HPP
