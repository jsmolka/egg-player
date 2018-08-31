#ifndef CONFIGAPP_HPP
#define CONFIGAPP_HPP

#include "configitem.hpp"

class ConfigApp : public ConfigItem
{
public:
    using ConfigItem::ConfigItem;

    void setDefaults() override;

    void setFontSize(double size);
    double fontSize();

    void setLog(bool log);
    bool log();
};

#endif // CONFIGAPP_HPP
