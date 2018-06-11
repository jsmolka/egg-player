#include "cfgapp.hpp"

CfgApp::CfgApp()
{

}

CfgApp::CfgApp(QJsonObject object)
    : CfgAbstract(object)
{

}

void CfgApp::setDefaults()
{
    setDefault("fontSize", 10.25);
    setDefault("log", true);
}

void CfgApp::setFontSize(double size)
{
    m_object.insert("fontSize", size);
}

double CfgApp::fontSize()
{
    return m_object.value("fontSize").toDouble();
}

void CfgApp::setLog(bool log)
{
    m_object.insert("log", log);
}

bool CfgApp::log()
{
    return m_object.value("log").toBool();
}
