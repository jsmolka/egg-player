#ifndef CONFIGBAR_HPP
#define CONFIGBAR_HPP

#include "configabstract.hpp"

class ConfigBar : public ConfigAbstract
{
public:
    using ConfigAbstract::ConfigAbstract;

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

    void setTimeWidth(int width);
    int timeWidth();

    void setTrackWidth(int width);
    int trackWidth();

    int coverSize();
};

#endif // CONFIGBAR_HPP
