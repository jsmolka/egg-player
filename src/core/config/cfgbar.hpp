#ifndef CFGBAR_HPP
#define CFGBAR_HPP

#include "cfgabstract.hpp"

class CfgBar : public CfgAbstract
{
public:
    CfgBar();
    CfgBar(QJsonObject object);

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

#endif // CFGBAR_HPP
