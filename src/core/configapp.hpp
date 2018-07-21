#ifndef CONFIGAPP_HPP
#define CONFIGAPP_HPP

#include "configabstract.hpp"

class ConfigApp : public ConfigAbstract
{
public:
    using ConfigAbstract::ConfigAbstract;

    void setDefaults() override;

    void setFontSize(double size);
    double fontSize();

    void setLog(bool log);
    bool log();
};

#endif // CONFIGAPP_HPP
