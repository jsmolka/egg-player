#ifndef CONFIGBAR_HPP
#define CONFIGBAR_HPP

#include "configitem.hpp"

class ConfigBar : public ConfigItem
{
public:
    ConfigBar();
    ConfigBar(const QJsonObject &object);
    ~ConfigBar();

    void setDefaults() override;

    void setGrooveHeight(int height);
    int grooveHeight();

    void setHandleSize(int size);
    int handleSize();

    void setHeight(int height);
    int height();

    void setIconSize(int size);
    int iconSize();

    void setMargin(int margin);
    int margin();

    void setSpacing(int spacing);
    int spacing();

    int coverSize();

    void setTimeWidth(int width);
    int timeWidth();

    void setTrackWidth(int width);
    int trackWidth();
};

#endif // CONFIGBAR_HPP
