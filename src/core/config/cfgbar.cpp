#include "cfgbar.hpp"

CfgBar::CfgBar()
{

}

CfgBar::CfgBar(QJsonObject object)
    : CfgAbstract(object)
{

}

void CfgBar::setDefaults()
{
    setDefault("grooveHeight", 2);
    setDefault("handleSize", 16);
    setDefault("height", 68);
    setDefault("iconSize", 32);
    setDefault("margin", 8);
    setDefault("spacing", 8);
    setDefault("timeWidth", 50);
    setDefault("trackWidth", 240);
}

void CfgBar::setGrooveHeight(int height)
{
    m_object.insert("grooveHeight", height);
}

int CfgBar::grooveHeight()
{
    return makeEven(scale(m_object.value("grooveHeight").toInt()));
}

void CfgBar::setHandleSize(int size)
{
    m_object.insert("handleSize", size);
}

int CfgBar::handleSize()
{
    return makeEven(scale(m_object.value("handleSize").toInt()));
}

void CfgBar::setHeight(int height)
{
    m_object.insert("height", height);
}

int CfgBar::height()
{
    return makeEven(scale(m_object.value("height").toInt()));
}

void CfgBar::setIconSize(int size)
{
    m_object.insert("iconSize", size);
}

int CfgBar::iconSize()
{
    return makeEven(scale(m_object.value("iconSize").toInt()));
}

void CfgBar::setMargin(int margin)
{
    m_object.insert("margin", margin);
}

int CfgBar::margin()
{
    return scale(m_object.value("margin").toInt());
}

void CfgBar::setSpacing(int spacing)
{
    m_object.insert("spacing", spacing);
}

int CfgBar::spacing()
{
    return scale(m_object.value("spacing").toInt());
}

int CfgBar::coverSize()
{
    return height() - 2 * margin();
}

void CfgBar::setTimeWidth(int width)
{
    m_object.insert("timeWidth", width);
}

int CfgBar::timeWidth()
{
    return scale(m_object.value("timeWidth").toInt());
}

void CfgBar::setTrackWidth(int width)
{
    m_object.insert("timeWidth", width);
}

int CfgBar::trackWidth()
{
    return scale(m_object.value("trackWidth").toInt());
}
