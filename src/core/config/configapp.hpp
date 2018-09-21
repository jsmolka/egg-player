#ifndef CONFIGAPP_HPP
#define CONFIGAPP_HPP

#include "configitem.hpp"

class ConfigApp : public ConfigItem
{
public:
    using ConfigItem::ConfigItem;

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

#endif // CONFIGAPP_HPP
