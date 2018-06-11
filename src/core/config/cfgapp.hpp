#ifndef CFGAPP_HPP
#define CFGAPP_HPP

#include "cfgabstract.hpp"

class CfgApp : public CfgAbstract
{
public:
    CfgApp();
    CfgApp(QJsonObject object);

    void setDefaults() override;

    void setFontSize(double size);
    double fontSize();

    void setLog(bool log);
    bool log();
};

#endif // CFGAPP_HPP
